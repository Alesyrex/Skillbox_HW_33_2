#include <iostream>
#include <vector>
#include <ctime>
#include <exception>

class BootException : std::exception
{
public:
    const char* what() const noexcept override
    {
        return "You caught the boot.";
    }
};

class FishException : std::exception
{
public:
    const char* what() const noexcept override
    {
        return "You caught the fish!";
    }
};

enum PondContent
{
    BOOT,
    FISH,
    NOTHING
};

int main() {
    srand(time(nullptr));
    std::vector<PondContent> pond (9,NOTHING);
    int countBoot = 3;
    bool fishing = true;
    int sector = 0;

    pond[rand()%pond.size()] = FISH;
    for (int i=0;i < countBoot;)
    {
        int random = rand()%pond.size();
        if(pond[random] == NOTHING)
        {
            pond[random] = BOOT;
            ++i;
        }
    }

    while (fishing)
    {
        std::cout << "In which sector(1-9) to throw a fishing rod?" << std::endl;
        std::cin >> sector;
        try
        {
            if (sector < 1 || sector > 9) throw std::invalid_argument("sector");
            switch (pond[sector-1])
            {
                case FISH:
                    throw FishException();
                case BOOT:
                    throw BootException();
                case NOTHING:
                    std::cout << "Try again!" << std::endl;
                    break;
            }
        }
        catch (std::invalid_argument &x)
        {
            std::cerr << "Invalid argument: " << x.what() << std::endl;
            fishing = false;
        }
        catch (BootException &x)
        {
            std::cerr << x.what() << std::endl;
            fishing = false;
        }
        catch (FishException &x)
        {
            std::cerr << x.what() << std::endl;
            fishing = false;
        }
    }

    return 0;
}
