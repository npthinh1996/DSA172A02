/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : Student code for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"

/// Initialize and Finalize any global data that you use in the program

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    string req = request.code;
    cout<<req<<": ";

    // TODO: Kiểm tra thiết bị ID có đi qua vị trí R trên trục y không
    if(req.substr(0,3) == "CYR"){
        cout<<"Yes"<<endl;
    }

    // TODO: Kiểm tra thiết bị ID có đi qua vị trí R trên trục x không
    if(req.substr(0,3) == "CXR"){
        cout<<"Yes"<<endl;
    }

    // TODO: Tìm số lượng record của thiết bị ID ở gần vị trí R trên trục y
    if(req.substr(0,3) == "NYR"){
        cout<<"0"<<endl;
    }

    // TODO: Tìm số lượng record của thiết bị ID ở gần vị trí R trên trục x
    if(req.substr(0,3) == "NXR"){
        cout<<"0"<<endl;
    }

    // TODO: Tìm số lần thiết bị ID đi qua vị trí R
    if(req.substr(0,3) == "NPR"){
        cout<<"0"<<endl;
    }

    // TODO: Tìm số thiết bị có hành trình đi qua vị trí R
    if(req.substr(0,3) == "NVP"){
        cout<<"0"<<endl;
    }
    
    // TODO: Tìm số record nằm gần vị trí R
    if(req.substr(0,3) == "NRR"){
        cout<<"0"<<endl;
    }

    // TODO: Kiểm tra xem thiết bị ID có hành trình đi qua vị trí R không
    if(req.substr(0,3) == "CVP"){
        cout<<"Yes"<<endl;
    }

    // TODO: Tìm số lượng record của thiết bị ID nằm gần vị trí R
    if(req.substr(0,3) == "NRP"){
        cout<<"0"<<endl;
    }

    return true;
}
