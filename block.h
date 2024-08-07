#define PICOJSON_USE_INT64
#include"picojson.h"
#include <memory>
#include <utility>
#define BLOCK_TYPE_MAX 52
#define BLOCK_TYPE_MIN 48
using std::cout;
using std::string;
using std::vector;



struct Position
{
    int64_t row;
    int64_t col;
};

class Block
{
private:
    Position pos;
    int64_t type;
public:
    Block(const int block_type,Position pos);
    ~Block();
    auto toJson() ->picojson::value;
};
