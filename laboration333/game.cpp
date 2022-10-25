#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
#include <memory>  // To take advantage of unique_ptr
#include <stdexcept> // std::out_of_range

//terminal color codes only for linux
#define RESET  "\033[0;0m"
#define RED    "\033[0;31m"
#define YELLOW "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BOLD   "\033[1m\033[0;0m"

#include "bag.h"
#include "game.h"
#include "goblin.h"
#include "wizard.h"
#include "terminal.h"
#include "bag.h"
#include "room.h"
#include "merlin_cave.h"
#include "dragon_factory.h"
#include "excalibur.h"
#include "bad_format.h"

/** NOTE: RAII (Resource Acquisition Is Initialization) is a programming idiom used
    in several object-oriented languages like C++, D, Ada and Vala. RAII is vital
    in writing exception-safe C++ code. Raii can be shortly explained as 'Every resource
    requiring cleanup should be given to an object's constructor'. In other words:
    -- Pointers should be encapsulated in smart pointer classes (std::shared_ptr and 
       std::unique_ptr for example).
    -- Handles requiring cleanup should be encapsulated in classes that automatically
       free/release the handles upon destruction.
    -- Synchronization should rely on releasing the mutex/synchronisation primitive 
       upon scope exit (see std::mutex, std::lock_guard)
*/

namespace camelot {

    std::vector<Actor *> * Game::actors;
    std::vector<Environment *> * Game::envs;

    Player *Game::player;

/* This class plays the role of the "controller" in the Model-View-Controller (MVC)
    as a DESIGN PATTERN. */

// constructor 
    Game::Game() {  

        // create the actors and the environments as help vectors for 'saveFile' 
        // but when we must 'delete' them ? TODO
        actors = new std::vector<Actor *>;
        envs = new std::vector<Environment *>;
    }

// destructor ..................................................................
    Game::~Game() 
    {
        //for (std::vector<Actor *>::iterator it = actors->begin(); it != actors->end(); ++it) {
        //    delete *it; }
               
			        //delete actors; //TODO
                                //delete envs;
        actors->clear(); // delete all the elements => only pointers to the actors
                         // but the actors themselves stay in memory
        delete commands;

        //delete player;
        //clear_game();
    }

// run_game()---------Main Loop of the Game  -----------------------------------
    // Remember: this procedure was implemented in the constructor first
    void Game::run_game()
    {   /*
        // create the actors and the environments as help vectors for 'saveFile' 
        // but when we must 'delete' them ? TODO
        actors = new std::vector<Actor *>;
        envs = new std::vector<Environment *>;
        */
        bool is_running = true;

        // initialize the game IF "saveFile" isn't good/ready      FIXME
        // otherwise load the file. //     
        loadOrInit();

        // print the introduction of the game on the screen
        printStory();

        while (is_running && playerIsAlive() && !playerIsAlone()) 
        {
            Terminal::print(player->get_room()->description());

            switch (terminal.parser()) {
                case 1:
                    is_running = false;
                    break;

                case 2:
                    // save actors and environments to 'saveFile' using vectors//
                    save();
                    is_running = false;
                    break;

                case 3:
                    //clear_game(); //Remove the help vectors: environments and actors FIXME
                                    //which we used to build 'saveFile' 
                    std::cout << actors->size() << " actors" << std::endl;
                    std::cout << envs->size() << " environments" << std::endl;
                    loadOrInit();  // FIXME
                    break;

                default:
                    run();  //let all the actors do their own 'actions'
                    break;
            }
        }
        if (!playerIsAlive()) {
            std::cout << "\n\t Sorry, you are defeated!...Game is over! :(" 
                      << "\n" << std::endl;
        }
        if (playerIsAlone()) {
            std::cout << "\n\t Congratulations! \n\t You have completed Merlin Game!" 
                      << "\n" << std::endl;

            //delete player;
            //std::unique_ptr<Player> up(player); // up now owns player
        }
        
    }


// playerIsAlive() .............................................................
    bool Game::playerIsAlive() {
        return player != nullptr;
    }

// initialize() ----------------------------------------------------------------
    /*
     * Create the map and all objects
     */
    void Game::initialize() {

        // Create Environments
        Environment * r1 = new Room(); // derived-to-base conversion
        Environment * r2 = new Room();
        Environment * cave = new MerlinCave();
   
        // Dragons som vaknar upp och börjar gå omkring
        new DragonFactory(cave, 2);
        // cave->enter(*drag_fac);
        
        // Create exits
        Exit * e1 = new Exit(r1, true, "e1", true);
        //std::unique_ptr<Exit> e1(new Exit(r1, true, "e1", true));

        Exit * e2 = new Exit(r2);
        //std::unique_ptr<Exit> e2(new Exit(r2));

        Exit * mcave = new Exit(cave, true, "cave", true);
        //std::unique_ptr<Exit> mcave(new Exit(cave, true, "cave", true));

       	//r1->add_exit("north", e1);  // FIXME
        r1->add_exit("west", e2);
        r1->add_exit("east", mcave);
        r2->add_exit("west", mcave);
        cave->add_exit("east", e2);
        cave->add_exit("west", e1);

        // ------ Create objects
        Object * b1 = new Bag();
        Object * b2 = new Bag();
        Object * b3 = new Bag();

        Object * b4 = new Food(47);

        Object * k1 = new Key("e1");
        Object * k2 = new Key("cave");

        r1->drop(b1);
        r1->drop(b2);
        r1->drop(b3);
        r1->drop(k2);

        r2->drop(b4);
        
        // ------ Create the sword
        Object * sword = new Excalibur(1000,0.95);
        cave->drop(sword);
        cave->drop(k1);


        // ------- Create the player
        player = new Player(r1);
        //std::unique_ptr<Player> up(player); // up now owns player
        //player = new Player(r1);
        r1->enter(*player);
        commands = new Commands(player);


        // ------- Initialize actors
        //std::shared_ptr<Goblin> spg = std::make_shared<Goblin>(r2, 1000, 88);
        new Goblin(r2, 1000, 88);
        // r2->enter(*t);

        //Wizard * w = new Wizard(cave, true, 100, 100);
        new Wizard(cave, true, 100, 100);
                      // cave->enter(*w);

        Bag bag;
    }

// run() .......................................................................
    void Game::run() {
        for (unsigned int i = 0; i < actors->size(); ++i) {
            actors->at(i)->action();
        }
    }

// add_actor() .................................................................
    void Game::add_actor(Actor &actor) {
        actors->push_back(&actor);
    }

// add_environment() ...........................................................
    void Game::add_environment(Environment &env) {
        envs->push_back(&env);
    }

// remove_actor() ..............................................................
    void Game::remove_actor(Actor &actor) 
    {
        if (&actor == player) {
            //player = 0;
            player = nullptr;  // FIXME
        }
        std::vector<Actor *>::iterator it = actors->begin();
        for (; it != actors->end(); ++it) 
        {
            if (&(**it) == &actor) 
            {
                actors->erase(it);   //erasing from STL containers invalidates 
                //*it = nullptr;    //any iterator associated with them
                return;
            }
        }
    }

// playerIsAlone() -------------------------------------------------------------
    bool Game::playerIsAlone() {
        return (playerIsAlive() && (actors->size() == 1));
    }

// printStory() ................................................................
    void Game::printStory() {
        Terminal::print("Background:\n    In a land of myth, and time of magic, the destiny of a great kingdom rests on the shoulders of a young boy. His name: Merlin. Merlin is a young wizard who arrives in the kingdom of Camelot after his mother arranges for him to stay with the court physician, Gaius. He discovers that the king, Uther Pendragon, has outlawed magic and imprisoned the Great Dragon 'Kilgharrah' in a vast cavern deep under the kingdom. After hearing a mysterious voice inside his head, Merlin makes his way to the cavern beneath Camelot where the Dragon tells Merlin that he plays an important role: to protect Uther's son, Arthur, who will bring forth a great kingdom. The Great Dragon gives Merlin grudging advice and forges the sword of Excalibur in his breath for Arthur, but persistently demands his freedom in return. Merlin eventually does release him...\n As mortal weapons cannot kill Morgana, Excalibur is the only weapon that can slay her. As the prophecy states, she died by Merlin's hand. Merlin calls the Great Dragon to carry him and Arthur to Avalon.");
    }

 //--------------------- Coding load/save game functions -----------------------
// save() ......................................................................
 // Save() open a output file stream for saving actors and environments to it
    void Game::save() 
    {
        std::fstream osfile;
      
        /* NOTE: 'ios::trunc' Openmode means that if the file opened for output 
           operations already existed before, its prefvious content is deleted 
           and replaced by the new one.  */

        osfile.open ("saveFile", std::fstream::out | std::fstream::trunc); 
        //osfile.open ("saveFile", std::ios_base::out | std::ios_base::trunc); 
        //osfile.open("saveFile", std::fstream::out | std::fstream::app);

        /* NOTE: The only way to preserve the existing data in a file opened by
           an ofstream is to specify 'app' or 'in' mode explicitly. (Lippman p320)*/

        // std::fstream fstrm;
        // fstrm.open("saveFile", mode)
        //if (!osfile.is_open())  // TODO
		//throw std::runtime_error(" \n\t Unable to open 'saveFile'");

        //for (auto it : actors) {
        for (std::vector<Actor *>::iterator it = actors->begin(); 
             it != actors->end(); ++it) 
        {
            (*it)->saveAct(osfile);
            //(*it)->saveAct(osfile);

        }

        //  for (auto it : envs) {
        for (std::vector<Environment *>::iterator it = envs->begin(); 
             it != envs->end(); ++it) 
        {
            //(*it)->saveEnv(osfile);
            (*it)->saveEnv(osfile);
        }

        osfile.close();
    }

// loadOrInit() ----------------------------------------------------------------------
   /* initialize the game IF "saveFile" isn't good      FIXME
      otherwise load the file. */  
    void Game::loadOrInit() {

        std::ifstream ifile("saveFile");  // input file stream to read from
        
        // good() checks whether the stream is ready for input/output operations
        if (!ifile.good()) {
            std::cout << "\n\t saveFile does not exist...We begin a new Game" 
                      << "\n" << std::endl;

            // #### Create the map and all objects
            initialize();

            return;
        }
        
        //############# load process begin here ##################################
        //std::cout << " Ciaoo Ciaooo" << std::endl; // FIXME
        std::string line;
       
        std::vector<std::string> * lines = new std::vector<std::string>;
    
        std::map<std::string, Environment *> created_envs; // keys are strings
        std::map<std::string, Object *> created_objects;  
        std::map<std::string, Exit *> created_exits;     

        // the while loop reads the file line by line using getline 
        while (std::getline(ifile, line)) {
            			//std::cout << line;
            lines->push_back(line);

            std::string line_token3 = line.substr(0, 3);
            std::string id_token = line.substr(0, line.find_first_of(':'));
            id_token = id_token.substr(3);
            
            if (line_token3 == "ACT" || line_token3 == "EXI") {
                // supress warnings for actors, which is handled later
            }

            else if (line_token3 == "ENV") {
                Environment *line_env = Environment::loadEnv(line); //??????
                std::cout << " \t Loading new environment:" << id_token << std::endl;
                created_envs[id_token] = line_env;

                // add_environment(*environment);
            }

            else if (line_token3 == "OBJ") {
                Object *line_obj = Object::loadObj(line);

                if (line_obj == nullptr)
                    std::cerr << "Game::loadOrInit(): NULL OBJECT RETURNED !! " 
                              << std::endl;
                created_objects[id_token] = line_obj;
                // add_object(*object);
            }
 
            else {
                std::cerr << "Invalid object type in save file: " 
                          << line_token3 << std::endl;
                throw BadFileFormatException();
            }
        } //while end
 
        //OBJECTS from lines   ......      .......   ...........
        /* NOTE:we can also use a "range for" to process the elements, 
           BUT we cannot use a range for to add elements to a vector
           or other container. In a range for end() is cached */

        // for (auto it : lines) {
        for (std::vector<std::string>::iterator it = lines->begin(); 
             it != lines->end(); ++it) {

            line = *it;

            std::string line_token3 = line.substr(0, 3);
            std::string id_token = line.substr(0, line.find_first_of(':'));
            id_token = id_token.substr(3);

            // Put all objects into their environments
            if (line_token3 == "ENV") {
                std::string line_objects = line.substr(line.find_first_of(':')+1);
                line_objects = line_objects.substr(0,line_objects.find_first_of(':'));

                while (true) {
                    std::string object = line_objects.substr(0,line_objects.find_first_of(','));
                    object = object.substr(3);
                    
                    if (created_objects.find(object) == created_objects.end())
                        std::cerr << "Game::load(): object NOT FOUND" << std::endl;
                    created_envs[id_token]->drop(created_objects[object]);  

                    if (created_objects.erase(object) == 0)
                        std::cerr << "ERROR: Didn't remove anything" << std::endl;
                    

                    if (line_objects.find_first_of(',') == std::string::npos)
                        break;
                    line_objects = line_objects.substr(line_objects.find_first_of(',')+1);

                }
            }
            // Put all objects into their containers
            else if (line_token3 == "OBJ") {

                // Only interesting of obj is a container
                Container *bag = dynamic_cast<Container *>(created_objects[id_token]);

                if (bag != nullptr) {
                    // we got a container
                    std::string line_objects = line.substr(line.find_first_of(':')+1);
                    line_objects = line_objects.substr(line_objects.find_first_of(':')+1);
                    line_objects = line_objects.substr(0,line_objects.find_first_of(':'));

                    // Lets go through the objects that should be inside our container
                    while (line_objects.length() > 0) {
                        std::string object = 
                        line_objects.substr(0,line_objects.find_first_of(','));

                        object = object.substr(3);

                        bag->add(*created_objects[object]);
                        created_objects.erase(object);

                        if (line_objects.find_first_of(',') == std::string::npos)
                        // 'npos' is the greatest possible value for an element of type size_t
                        // it is usually used to indicate no matches 
                            break;
                        line_objects = line_objects.substr(line_objects.find_first_of(',')+1);

                    }
                }
            }
        }
        // ACTORS from lines      ..................     .......................
        // Loop through the actors again, they need initalized envs and objs
        for (std::vector<std::string>::iterator it = lines->begin(); 
             it != lines->end(); ++it) {

            line = *it;
            std::string line_token3 = line.substr(0, 3);
            std::string id_token = line.substr(0, line.find_first_of(':'));
            id_token = id_token.substr(3);

            if (line_token3 == "ACT") {
                Actor *actor = Actor::loadAct(line, created_envs, created_objects);
 
                if (actor != nullptr) {
                    Player *player = dynamic_cast<Player *>(actor);

                    if (player != nullptr) {
                        commands = new Commands(player);
                        this->player = player;

                    }
                }

            }

            else if (line_token3 == "EXI") {
                Exit * exit =  Exit::loadExi(line, created_envs);
                created_exits[id_token] = exit;
            }
        }

        // ENVIRONMENTS from lines    ...........          ...................
        for (std::vector<std::string>::iterator it = lines->begin(); 
             it != lines->end(); ++it) {

            line = *it;
            std::string line_token3 = line.substr(0, 3);
            std::string id_token = line.substr(0, line.find_first_of(':'));
            id_token = id_token.substr(3);

            if (line_token3 == "ENV") {
                std::istringstream input(line);
                std::vector<std::string> tokens;
                std::string token;

                while (std::getline(input, token, ':')) {
                    tokens.push_back(token);
                }

                std::map<std::string, std::string> properties;

                std::istringstream pss(tokens[3]);
                while (std::getline(pss, token, ',')) {
                    size_t eq_sign = token.find('=');
                    properties.insert(std::pair<std::string,
                                                std::string>(token.substr(0, eq_sign), 
                                                             token.substr(eq_sign+1)));
                }

                for (std::map<std::string,
                              std::string>::iterator it = properties.begin();
                     it != properties.end(); ++it) {
                    created_envs[id_token]->add_exit(it->second, 
                                               created_exits[it->first.substr(3)]);
                }
            }

        }

        delete lines;  // ###########################
        ifile.close();   //##########################
    }

/*
// clean_exits()  FIXME
   void Environment::clean_exits()
   {
     for (auto keyvalue : exits)
     {
       delete keyvalue.second;  
     }
     exits.clear(); // Removes all the elements (pointers to 'exits') from the map container  
                    // (exits are destroyed before by 'delete'), 
                    // leaving the container with a size of 0.
   }
*/

// clear_game() ----------------------------------------------------------------
    // destroys the help vectors: environments and actors 
    // which we used to build 'saveFile'  
    
    void Game::clear_game() 
    {
        std::cout << " \t Removing environments" << std::endl;
        //for (auto env_it : envs) { delete *env_it; }
        for (std::vector<Environment *>::iterator it = envs->begin(); it != envs->end(); ++it) {
            delete *it;
        }
        // envs.clear(); // delete pointers to envs

        std::cout << " \t Killing players" << std::endl;
        //for (auto act_it : ators) { delete *act_it; }
       for (std::vector<Actor *>::iterator it = actors->begin(); it != actors->end(); ++it) {
            delete *it;
       }
       // actors.clear(); // delete pointers to actors after we destroyed 
                          // the elements stored in memory 
    }
}
// --------------------------- main() ------------------------------------------
int main() {

    std::cout << RESET << std::endl;  // reset the default color.
   
    std::cout << " \n\t\t *******************************************" << std::endl;
    std::cout << "   \t\t * Welcome to the Role-playing Game Merlin *" << std::endl;
    std::cout << "   \t\t *******************************************" << std::endl;
    
    /* NOTE: Call to function srand (from "stdlib.h") 
       should initialize a random number generator built into c++ before
       using it; current system time (from "time.h") is used to initialize
       randomization. */

    // Initialize random seed
    // std::default_random_engine e(time(0)); // C++11 
    std::srand(std::time(0));
    
    camelot::Game game;
    game.run_game();
     
    //game.clear_game();  //TODO
    //delete player;

    
}

