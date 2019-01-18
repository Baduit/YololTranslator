#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>
#include <cstring>

#include "SentenceTranslator.hpp"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cout << "Mettez en argument la phrase à traduire." << std::endl;
        return 1;
    }

    std::string dico_dir = "./dico/";
    if (argc > 2)
        dico_dir = argv[2];

    GoodToBad goodToBad(dico_dir);
    std::cout << goodToBad.translate(argv[1]) << std::endl;
}