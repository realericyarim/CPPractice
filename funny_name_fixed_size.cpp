#include <iostream>
#include <stdexcept>
#include <cstring>
//program to manually get the length of a string (DONE), copy it (IMPLEMENTED IN ANOTHER WAY), and reverse it 
//and also build a dynamic array with push pop and manual reallocation? (kinda done lol maybe later)

class dynamic_array {
public: //stuff program can touch ,also note its malloc<>free or new<>delete[]
    dynamic_array() {
        memory_capacity = 8;
        stored_elements = 0;
        real_data_home = new char[memory_capacity];
        //constructor method running when class created (eg allocated memory)
        //can allocate our new data for an array
    }

    ~dynamic_array() {
        delete[] real_data_home;
        //destructor method running automatically when class destroyed
        //can deallocate our memory
    }

    void expand_push(char value) {  //takes one lettter at a time
        if (stored_elements >= memory_capacity) { //eh do we use a while loop if we're adding a shit ton of data but we're not just one character
            resize(); //up our array size
        }
        real_data_home[stored_elements] = value; //you will live at the apartment corresponding to how many pieces we have
        stored_elements++; //updatesd how many pieces we have so we know to go to next spot
    }

    int size() const { //tjos method will not modify the stuff inside of it! is prupose of const im so tired ahhhh
        return stored_elements;
    }

    char step(int index) const {
        if (index < 0 || index >= stored_elements) {
            return '\0';
        }
        return real_data_home[index]; //so go to that real_data_home the pointer to the beginning of your array, and give me what lives at said index!
    }

private: //stuff that rest of program cant touch
    char* real_data_home; //an address of the actual data so we will free up those addrtesses
    int stored_elements;
    int memory_capacity;

    void resize() {
        int updated_capacity = 2 * memory_capacity; //our new apartment will be double the size
        char* new_data_home = new char[updated_capacity]; //our new apartment is now built and is actualyl double the size, 
        //now we are actualyl building the apartment, the pointer new_data is saying hey our new apartment is phyiscally built with 2x the units

        for (int i = 0; i < stored_elements; i++) {
            new_data_home[i] = real_data_home[i]; //datas are pointers to first elements of arrays, we say go from old apartment to new apartment
        } //ok this is annoying but arrays decay to pointers. so array[i] is pointer[i] cus pointer is first element

        delete[] real_data_home; //we blew up their old apartment. note that data just means addresses, so their old addresses are gone to their new addreses
        real_data_home = new_data_home;
        memory_capacity = updated_capacity;
    }
};

int string_length(const char* name) {
    int iterator = 0;

    while (name[iterator] != '\0') {
        iterator++;

        if (name[iterator] == '\0') {
            break;
        } else {
            continue;
        }
    }

    return iterator;
}

dynamic_array reverse(const dynamic_array& original) { //the single & means that we can take the reference to dynamic array, not the actual item, just reference
    dynamic_array reversed;

    for (int i = original.size() - 1; i >= 0; i--) {
        char c = original.step(i);
        reversed.expand_push(c); //get the original character at index max, and push it to position 0. and expand push will grow the array as needed!
    }

    return reversed;
}

int main(void) {
    char first_name[5]; //so this is cool any addresses after the users name are auto filled with terminators 

    while (true) {
        std::cout << "Enter a string: ";
        std::cin.getline(first_name, 5); //great opportunity to implement both dynamic array and copying!!!! dynamic array for cin buffer, and copy for memory safety!

        if (std::cin.fail()) {
            std::cout << "eh you got a funny long name eh?" << std::endl;
            dynamic_array long_first_name;

            for (int i = 0; i < string_length(first_name); i++) {
                long_first_name.expand_push(first_name[i]); //this gets the OG part and just copies whats already in our first name
            }

            std::cin.clear(); //clear failbit before attempting to read cause the system triggers the no no alert for biolating the std input size thign

            // read any leftover characters using peek to detect if there's still input
            while (std::cin.peek() != '\n' && std::cin.peek() != EOF) { //we keep looking through the stream until we get to the end of it if its not newline or end
                char c;
                std::cin.get(c); //get recovers it
                long_first_name.expand_push(c);
            }
            std::cin.get(); // remove trailing newline

            try {
                char choice;
                std::cout << "ok funny guy, do you want your name shortened to fit the proper parameters? y/n" << std::endl;
                std::cin >> choice;
                std::cin.ignore(1000, '\n'); //flush anmd get rid of the last of it!

                if (choice == 'y') {
                    std::cout << "Hi ";
                    for (int i = 0; i < 5; i++) {
                        std::cout << first_name[i];
                    }
                    std::cout << ", Nice to meet you!, are you an anlien?" << std::endl;
                } else if (choice == 'n') {
                    dynamic_array reversed_first_long = reverse(long_first_name);
                    std::cout << "Hi ";
                    for (int i = 0; i < reversed_first_long.size(); i++) {
                        std::cout << reversed_first_long.step(i); //so I have to use my own custom index thing, equivalent to [i] cus its not common to new data structures
                    }
                    std::cout << ", Nice to meet you! are you an alien?" << std::endl; //step(i) just works as a custom index for the private junk there, but you can reimp
                } else if (choice != 'y' && choice != 'n') {
                    throw std::runtime_error("Dude that input will not cut it");
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << '\n';
                std::cout << "you have been cursed with a hundredfold memory leak for not cooperating :(";
                std::cin.clear();

                int* leak = new int[100]; //so we just got 100 pieces of heap memory and we will never delete them
                //these hundred addresses shall never be filled leaking the real estate developer money on da heap
            }
        } else {
            break;
        }
    }

    //then lets just reverse the completed name for fun and thats game!
    //update it was hell on earth and I never want to do that again. because I made it waaaaay too har.
    return 0;
}
