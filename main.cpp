#include "picojson.h"
#include "block.h"
#include <cctype>
#include <fstream>

// read in map data from file thet the path indicetes
// content check is ignored
vector<string> readIn(const string path)
{
    vector<string> mapInfo;
    std::ifstream file(path);
    if (file.is_open())
    {
        // open succeeded, read in lines and push_back
        string line;
        while (std::getline(file, line))
        {
            mapInfo.push_back(line);
            std::cout << line << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
        exit(0);
    }
    return mapInfo;
}

void ensureArgcValid(const int argc)
{
    if (argc != 2)
    {
        printf("usage：map <map description file>\n");
        exit(1);
    }
}

void initObjList(vector<vector<Block>> &blockList, const vector<string> &mapInfo)
{
    blockList.resize(mapInfo.size()); // block list row number init
    for (int i = 0; i < mapInfo.size(); i++)
    {
        auto row = &blockList[i];
        // init one row
        for (int j = 0; j < mapInfo[i].size(); j++)
        {
            char num = mapInfo[i][j];
            if (num == ' ' | num == '\t')
                continue;                                 // skip blank
            if (num<BLOCK_TYPE_MIN | num> BLOCK_TYPE_MAX) // only 0-4 permitted
            {
                printf("char in row %d col %d is not valid\n", i, j);
            }
            // char is valid, convert to Block obj
            row->push_back(Block(num, Position{i, j}));
        }
    }
}

picojson::value genJsonObj(const vector<vector<Block>> &blockList)
{
    picojson::array root;

    for (size_t i = 0; i < blockList.size(); i++)
    {
        auto row = &blockList[i];
        picojson::array json_row;
        for (size_t j = 0; j < row->size(); j++)
        {
            auto block = (*row)[j];
            auto block_json=std::move(block.toJson());
            cout<< block_json;
            // json_row.push_back(block_json);
        }
        cout<<picojson::value(json_row);
        root.push_back(picojson::value(json_row));
    }

    return picojson::value(root);
}


int main(int argc, char const *argv[])
{
    printf("%d\n", argc);
    ensureArgcValid(argc);
    const string inputPath = argv[1];
    auto mapInfo = readIn(argv[1]);
    // convert to object List
    vector<vector<Block>> blockList;
    initObjList(blockList, mapInfo);
    // convert to json object List
    auto jsonObj = genJsonObj(blockList);

    return 0;
}
