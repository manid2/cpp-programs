// Learn GCov tool, sample code main funcion
#include "learn_gcov_func.hh"

// TODO: write better example to show gcov usage
int main(int argc, char **argv)
{
    float x, y;
    int choice;

    do {
        LGF::showChoices();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter two numbers: ";
            std::cin >> x >> y;
            std::cout << "Sum " << LGF::add(x, y) << std::endl;
            break;
        case 2:
            std::cout << "Enter two numbers: ";
            std::cin >> x >> y;
            std::cout << "Difference " << LGF::subtract(x, y) << std::endl;
            break;
        case 3:
            std::cout << "Enter two numbers: ";
            std::cin >> x >> y;
            std::cout << "Product " << LGF::multiply(x, y) << std::endl;
            break;
        case 4:
            std::cout << "Enter two numbers: ";
            std::cin >> x >> y;
            std::cout << "Quotient " << LGF::divide(x, y) << std::endl;
            break;
        case 5: break;
        default: std::cout << "Invalid input" << std::endl;
        }
    } while (choice != 5);

    return 0;
}
