#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

#include "stdafx.h"
#include "resource.h"
#include "plu.h"

using namespace std;

vector<string> split (string s, string delimiter);
int str_ip_to_int (string str_ip);

int main(int argc, char** argv)
{
    if (argc < 3) {
        cout << "Missed Arguments: ip_address, plu_file_name" << endl;
        return 0;
    }

    char* ip_address = argv[1];
    char* plu_file_name = argv[2];

    cout << "adresse2: " << ip_address;

    HINSTANCE hDLL;               // Handle to DLL
    LPFNPBusConnect PBusConnect;
    LPFNPBusDisConnect PBusDisConnect;
    LPFNPBusTransferPLUCluster PBusTransferPLUCluster;
    LPFNPBusTransferHotkey PBusTransferHotkey;
    LPFNPBusPLUToStr PBusPLUToStr;
    LPFNPBusStrToPLU PBusStrToPLU;
    long ReturnVal;
    TPLU PLU;
    TPLUCluster PLUCluster;
    THotkeyTable HotkeyTable;
    char Str[256];
    char PLUName[256];
    char PLUCode[256];
    ReturnVal=0;

    hDLL = LoadLibrary("PBusDrv.dll");
    if (hDLL != NULL)
    {
        PBusConnect=(LPFNPBusConnect)GetProcAddress(hDLL,"PBusConnect");
        PBusDisConnect=(LPFNPBusDisConnect)GetProcAddress(hDLL,"PBusDisConnect");
        PBusTransferPLUCluster=(LPFNPBusTransferPLUCluster)GetProcAddress(hDLL,"PBusTransferPLUCluster");
        PBusTransferHotkey=(LPFNPBusTransferHotkey)GetProcAddress(hDLL,"PBusTransferHotkey");
        PBusPLUToStr=(LPFNPBusPLUToStr)GetProcAddress(hDLL,"PBusPLUToStr");
        PBusStrToPLU=(LPFNPBusStrToPLU)GetProcAddress(hDLL,"PBusStrToPLU");
        // Init
        memset(&PLU,0,sizeof(PLU));
        memset(&PLUCluster,0,sizeof(PLUCluster));
        memset(HotkeyTable,0,sizeof(HotkeyTable));
        
        // start insert data and send it to scale
        string line;
        ifstream plu_file(plu_file_name);
        int i = 1;
        while(getline(plu_file, line)) {
            cout << "line " + line << endl;
            vector<string> tokens = split(line, "\t");
            char name[tokens[0].size() + 1];
            strcpy(name, tokens[0].c_str());
            cout << name << endl;
            PLU.Name=name;
            PLU.LFCode=stol(tokens[1]);
            char code[tokens[2].size() + 1];
            strcpy(code, tokens[2].c_str());
            PLU.Code=code;
            PLU.BarCode=stol(tokens[3]);
            PLU.UnitPrice=stol(tokens[4]);
            PLU.WeightUnit=stol(tokens[5]);
            PLU.Deptment=stol(tokens[6]);
            PLU.ShlefTime=stol(tokens[7]);
            PLU.PackageType=stol(tokens[8]);
            PLU.Tolerance=stol(tokens[9]);
            PLUCluster[0]=PLU;
            HotkeyTable[0]=stol(tokens[1]);
            //test PBusPLUToStr
            memset(Str,0,256);
            ReturnVal=PBusPLUToStr(&PLU,Str);
            //test PBusStrToPLU
            memset(&PLU,0,sizeof(PLU));
            PLU.Name=PLUName;
            PLU.Code=PLUCode;
            ReturnVal=PBusStrToPLU(Str,&PLU);
            //Connect
            ReturnVal=PBusConnect(".\\lfzk.dat",".\\system.cfg",str_ip_to_int(ip_address),"IP",0);
                        //Transfer one PLU
            ReturnVal=PBusTransferPLUCluster(&PLUCluster);
            //Transfer Hotkey
            ReturnVal=PBusTransferHotkey(&HotkeyTable,0);
            //DisConnect
            ReturnVal=PBusDisConnect(0xC0A80157);
        }

        plu_file.close();
      }

    return 0;
}

vector<string> split (string s, string delimiter) {
    vector<string> res;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        cout << token << endl;
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    res.push_back(s);
    
    return res;
}

int str_ip_to_int (string str_ip) {
    auto v_ip = split(str_ip,".");
    int x = 0;
    for(auto i: v_ip){
        x=(x<<8)+stoi(i);
    }

    return x;
}
