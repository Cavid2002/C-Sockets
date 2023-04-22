#include"src/MYHTTP.h"




int main()
{
    http_server serv;
    serv.ip_family = AF_INET;
    serv.trcp_protocol = SOCK_STREAM;
    serv.q_size = 10;
    serv.port = 3340;


    http_route r1 = {.filename = "index.html",.method = GET, .path="/internal-image"};
    http_route r2 = {.filename = "index2.html",.method = GET, .path="/external-image"};
    http_route r3 = {.filename = "index3.html",.method = GET, .path="/"};
    http_route r4 = {.filename = "index4.html",.method = GET,.path="/video-test"};
    http_route r5 = {.filename = "form_test.html",.method = POST,.path = "/form-test"};
    create_route(&r1);
    create_route(&r2);
    create_route(&r3);
    create_route(&r4);
    create_route(&r5);

    
    server_init(&serv);
    
}