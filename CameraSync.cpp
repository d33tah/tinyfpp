#include "CameraSync.h"
#include "Camera.h"

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <utility> //std::pair

typedef std::pair<std::string, int> S_HostPortPair;
S_HostPortPair readServerCfgFile()
{
    S_HostPortPair ret;
    std::ifstream file("Data/server.cfg");
    file >> ret.first;
    file >> ret.second;
    return ret;
}

void die(std::string str)
{
    std::cerr << str << std::endl;
    exit(1);
}

#ifdef WIN32

//TODO: port to Windows
void CameraSync::sendSync(Camera c2){}
CameraSync::CameraSync(Camera& camera) : camera(camera);

#else

/*
 * TODO:
 *
 * - figure out if there are any locks needed
 * - logging system should be a separate class
 * - move camera serialization to its class?
 * - get rid of exit()?
 * - error checking?
 *
 */

#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <pthread.h>

#include "GL/gl.h"

typedef std::pair<int, Camera*> S_SockCameraPair;

typedef struct
{
    float xpos, zpos, ypos;
    GLfloat rotateX, rotateY, camx, camy, camz;
} S_CameraDefMsg;

void* syncLoop(void* obj)
{
    //TODO: I guess I need some locks there.
    S_SockCameraPair* para = (S_SockCameraPair*)obj;
    int sock = para->first;
    Camera* cam = para->second;
    delete para;

    for(;;){
        S_CameraDefMsg msg;
        if (recv(sock, (void*)&msg, sizeof(S_CameraDefMsg), 0) < 1) {
            die("Failed to receive bytes from server");
        }
        cam->rotateX = msg.rotateX;
        cam->rotateY = msg.rotateY;
        cam->camx = msg.camx;
        cam->camy = msg.camy;
        cam->camz = msg.camz;
        cam->zpos = msg.zpos;
        cam->xpos = msg.xpos;
    }
    return NULL;
}

void CameraSync::sendSync(Camera c2)
{
    S_CameraDefMsg msg;
    msg.rotateX = c2.rotateX;
    msg.rotateY = c2.rotateY;
    msg.camx = c2.camx;
    msg.camy = c2.camy;
    msg.camz = c2.camz;
    msg.zpos = c2.zpos;
    msg.xpos = c2.xpos;
    send(sock, (void*)&msg, sizeof(S_CameraDefMsg), 0);
}


CameraSync::CameraSync(Camera& camera) : camera(camera)
{
    struct sockaddr_in conn_params;
    S_HostPortPair serverCfgData = readServerCfgFile();

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&conn_params, 0, sizeof(conn_params));
    conn_params.sin_family = AF_INET;
    conn_params.sin_addr.s_addr = inet_addr(serverCfgData.first.c_str());
    conn_params.sin_port = htons(serverCfgData.second);

    if(connect(sock, (struct sockaddr *) &conn_params, sizeof(conn_params))<0)
    {
            std::stringstream ss;
            ss << "Failed to connect to ";
            ss << serverCfgData.first;
            ss << ":";
            ss << serverCfgData.second;
            die(ss.str());
    }

    S_SockCameraPair* para = new S_SockCameraPair(sock, &camera);
    pthread_t thread = pthread_create( &thread, NULL, syncLoop, (void*) para);
}

#endif
