#include "include/stdafx.h"





int main()
{
    virtualProtect(); // only need once
    std::thread t1(mempatch); // start first thread for integrity check
    dummythread(); // start dummy thread if this thread gets closed the programm will exit
    CheckDebugger(); // check for debugger x1
    flux::set_application(""); // enter your id here --> create account https://fluxauth.com/

    std::string usrKey;
    std::cout << dye::grey("["); std::cout << dye::aqua("<"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Enter License: ", 55 };
    std::cin >> usrKey;

    try {
       CheckDebugger();
        flux::authenticate(usrKey);       
    }

    catch (std::runtime_error& e) {    
        std::cout << '\n' << e.what();
        Sleep(1000);
        exit(1);
    }


main:
    system("cls"); std::thread t2(mempatch); CheckDebugger(); // second integrity check
    int option;

    std::cout << dye::grey("["); std::cout << dye::aqua("1"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Load Driver \n", 55 };
    std::cout << dye::grey("["); std::cout << dye::aqua("2"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Load Cheat \n\n\n", 55 };
    std::cout << dye::grey("["); std::cout << dye::aqua("<"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Select: ", 55 };

    std::cin >> option;
    switch (option) {

    case 1:
        system("cls");
        std::cout << dye::grey("["); std::cout << dye::aqua("!"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Loading Driver... \n\n", 55 };
        Sleep(3000);
        std::cout << dye::grey("["); std::cout << dye::green("+"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Success! \n", 55 };
        Sleep(1500);
        goto main;
        break;

    case 2:
        system("cls");
        std::cout << dye::grey("["); std::cout << dye::aqua("!"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Loading Cheat... \n\n", 55 };
        Sleep(3000);
        std::cout << dye::grey("["); std::cout << dye::green("+"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Success! \n", 55 };
        Sleep(1500);
        goto main;
        break;

    default:
        system("cls");
        std::cout << dye::grey("["); std::cout << dye::red("!"); std::cout << dye::grey("] "); std::cout << slowly_printing_string{ "Invalid Selection...\n", 55 };
        Sleep(2000);
        goto main;
        break;

    }
    return 0;
}