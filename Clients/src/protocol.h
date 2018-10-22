#include <vector>
#include <string>


class Protocol
{

public:

static std::vector<std::string> FromServer(std::string message);
static std::string  ToServer(std::vector<std::string> message);
static std::string  ToServer(std::string message);
static std::string makeString(std::vector<std::string> message, std::string startChar, std::string endChar);
static std::string makeString(std::string message, std::string startChar, std::string endChar);

private:
static std::vector<std::string> SplitString(std::string text, char split);


};