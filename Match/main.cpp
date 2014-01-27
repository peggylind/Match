
//
//  main.cpp
//  Match
//
//  Created by Peggy Lindner on 1/6/14.
//  Copyright (c) 2014 Peggy Lindner. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <string>
using namespace std;
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
using namespace boost;

#include <cstdio>

int main(int argc, const char * argv[])
{
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <OLDID file>" << " <NEWID file>"<< endl;
    }
    
    // file objects
    ifstream fin1, fin2;
    ofstream fout1, fout2;
    
    fin1.open(argv[1]); // open file 1
    fin2.open(argv[2]); // open file 2
    fout1.open ("match_10.txt");
    fout1 << "OLD_ID     NEW_ID" << endl;
    fout2.open ("match_8.txt");
    fout2 << "OLD_ID     NEW_ID" << endl;
    
    // exit if files not found
    if (!fin1.good() || !fin2.good())
    {
        cout << "One of the files could not be opend!" << endl;
        return 1;
    }
    
    string line1, line2;
    
    //skip the first 2 lines in 2nd file
    getline(fin2, line2);
    getline(fin2, line2);
    
    //store the 2nd file in memory
    vector<string> lines;
    vector<string>::iterator myIterator;
    
    typedef boost::unordered_map<int, int[11]> unordered_map;
    unordered_map map;
    
    while(!fin2.eof())
    {
        getline(fin2, line2);
        lines.push_back(line2);
        int offsets2[] = {9,4,3,5,7,4,4,4,4,4,12};
        offset_separator f(offsets2, offsets2+11);
        tokenizer<offset_separator> tok2(line2,f);
        
        string strArray2[11];
        copy(tok2.begin(), tok2.end(), strArray2);
    }
    
    fin2.close();
    
    //First pass
    cout << "Start ..." << endl;
    //skip the first two lines in first file
    getline(fin1, line1);
    getline(fin1, line1);
    
    // read each line of file 1
    while (!fin1.eof())
    {
        // read an entire line into memory and we need to skip the first 2 lines
        getline(fin1, line1);
        
        // parse the line into tokens using offsets
        int offsets[] = {9,4,3,5,5,4,4,4,4,4,12};
        offset_separator f(offsets, offsets+11);
        tokenizer<offset_separator> tok1(line1,f);
        
        //store values in int array
        string strArray[11];
        copy(tok1.begin(), tok1.end(), strArray);
        int storeVar1[10];
        for (int i = 1; i < 11; i++)
            sscanf(strArray[i].c_str(), "%d", &storeVar1[i - 1]);
        
        bool match = false;
        
        //loop over lines in memory and try to find match
        for(myIterator = lines.begin();
            myIterator != lines.end();
            myIterator++)
        {
            // parse the line into tokens using offsets
            int offsets2[] = {9,4,3,5,7,4,4,4,4,4,12};
            offset_separator f(offsets2, offsets2+11);
            tokenizer<offset_separator> tok2(*myIterator,f);
            
            string strArray2[11];
            copy(tok2.begin(), tok2.end(), strArray2);
            int storeVar2[10];
            for (int i = 1; i < 11; i++)
               sscanf(strArray2[i].c_str(), "%d", &storeVar2[i - 1]);
            
            //correct variable V4 (Year)
            storeVar2[3] = storeVar2[3] - 1900;
            
            // process (compare) the tokens and write to file
            if (storeVar1[2] == storeVar2[2] && storeVar1[3] == storeVar2[3] && storeVar1[4] == storeVar2[4] && storeVar1[5] == storeVar2[5] && storeVar1[6] == storeVar2[6] && storeVar1[7] == storeVar2[7] && storeVar1[8] == storeVar2[8] && storeVar1[9] == storeVar2[9])
            {
                fout2 << strArray[0] << "  " << strArray2[0] << endl;
                if (storeVar1[0] == storeVar2[0] && storeVar1[1] == storeVar2[1])
                    fout1 << strArray[0] << "  " << strArray2[0] << endl;
                match = true;
                break;
            }
            
        }
        
        if (!match)
            fout2 << strArray[0] << endl;
    }
    
    //Done!
    fin1.close();
    fout1.close();
    fout2.close();
    
    cout << "Reached end!" << endl;
    return 0;
}



