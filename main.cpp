#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "stdafx.h"
#include "resource.h"
#include "plu.h"

using namespace std;

vector<string> split (string s, string delimiter);

int main(int argc, char** argv)
{
    if (argc < 3) {
        cout << "Missed Arguments: ip_address, plu_file_name" << endl;
        return 0;
    }

    char* ip_address = argv[1];
    char* plu_file_name = argv[2];
    string line;

    ifstream plu_file(plu_file_name);

    int i = 1;
    while(getline(plu_file, line)) {
        cout << "line " << i++ << endl;
        vector<string> v = split (line, "\t");
        for(int j = 0; j < v.size(); j++){
            cout << v[i] << endl;
        }
        cout << endl;
    }

    plu_file.close();

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
        PLU.Name="moubid";
        PLU.LFCode=12345;
        PLU.UnitPrice=50000;
        PLUCluster[0]=PLU;
        HotkeyTable[0]=12345;
        //test PBusPLUToStr
        memset(Str,0,256);
        ReturnVal=PBusPLUToStr(&PLU,Str);
        //test PBusStrToPLU
        memset(&PLU,0,sizeof(PLU));
        PLU.Name=PLUName;
        PLU.Code=PLUCode;
        ReturnVal=PBusStrToPLU(Str,&PLU);
        //Connect
        ReturnVal=PBusConnect(".\\lfzk.dat",".\\system.cfg",0xC0A80157,"IP",0);
        //Transfer one PLU
        ReturnVal=PBusTransferPLUCluster(&PLUCluster);
        //Transfer Hotkey
        ReturnVal=PBusTransferHotkey(&HotkeyTable,0);
        //DisConnect
        ReturnVal=PBusDisConnect(0xC0A80157);
      }

    return 0;
}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
