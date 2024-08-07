#include "block.h"
Block::Block(const int block_type, Position pos)
{

    this->type = block_type;
    this->pos = pos;
}

Block::~Block()
{
}

auto Block::toJson() ->std::unique_ptr<picojson::value>
{
    picojson::object pos;
    pos.insert(std::make_pair("row", picojson::value(this->pos.row)));
    pos.insert(std::make_pair("col", picojson::value(this->pos.col)));

    picojson::object obj;
    obj.insert(std::make_pair("type", picojson::value(this->type)));
    obj.insert(std::make_pair("pos", pos));
    return std::make_unique<picojson::value>(obj);
}