#include <iostream>
#include <vector>
#include <sstream>

#include "WebCrawler.h"


int main()
{
    // http://www.my.com/pub/index.html
    // http://localhost:8000/pub/index.html
    // http://10.10.10.4:8000/pub/pub2/index.html

    /*std::string strInputUrl = "http://www.google.com/pub/pub2/index.html";

    CURLParser oURLParcer(strInputUrl);
    oURLParcer.Parce();

    std::cout << "Host: " << oURLParcer.GetHost() << std::endl;
    std::cout << "Path: " << oURLParcer.GetPath() << std::endl;
    
    unsigned short usPort = oURLParcer.GetPort();

    if (usPort != ZERO)
        std::cout << "Port: " << usPort << std::endl;*/

    // "<html><body></body></html>"; +
    // "<html></html>"; +
    // "<html><body><a href='http://10.10.10.4:8000/pub/pub2/index.html'></a>This is link</body></html>"; +
    // "<html><body><a href='http://10.10.10.4:8000/pub/pub2/index.html'></a></body></html>"; +
    // "<html><body>This is test</body></html>"; +
    // "<html><body><a href='http://10.10.10.4:8000/pub/pub2/index.html'>This is link</a></body></html>"; +
    // "<html><body>This is test<a>This is link</a></body></html>"; +
    // "<html><body>This is test<a href='http://10.10.10.4:8000/pub/pub2/index.html'>This is link</a></body></html>"; +
    // "<html><body>This is test<a href=\"http://10.10.10.4:8000/pub/pub2/index.html\">This is link</a></body></html>"; +

    /*std::string strInput =
        "<html><body>This is test<a href='http://crawlertest.cs.tu-varna.bg/TestIIR.html'>This is link</a></body></html>";

    CHTMLParser oHTMLParser(strInput);
    oHTMLParser.Parse();

    std::string strURL = oHTMLParser.GetURL();
    std::cout << strURL << std::endl;

    CURLParser oURLParser(strURL);
    oURLParser.Parse();

    std::cout << oURLParser.GetHost() << std::endl;
    std::cout << oURLParser.GetPort() << std::endl;
    std::cout << oURLParser.GetPath() << std::endl;*/
    
    /*std::string strURL = "http://crawlertest.cs.tu-varna.bg/TestIIR.html";

    WebCrawler oWebCrawler(strURL);
    oWebCrawler.Run();
    oWebCrawler.PrintIndexInfo();*/

    InvertedIndex oInvertedIndex("words.txt");
    oInvertedIndex.Construct();
    oInvertedIndex.PrintInfo();

    /*BinaryTree oBinaryTree;

    oBinaryTree.AddNode("zaza", std::pair<short, size_t>(1, 1));
    oBinaryTree.AddNode("baba", std::pair<short, size_t>(2, 2));
    oBinaryTree.AddNode("baba", std::pair<short, size_t>(3, 3));
    oBinaryTree.AddNode("elephant", std::pair<short, size_t>(3, 4));
    oBinaryTree.AddNode("elephant", std::pair<short, size_t>(2, 5));
    oBinaryTree.AddNode("elephant", std::pair<short, size_t>(1, 8));
    oBinaryTree.AddNode("zaza", std::pair<short, size_t>(2, 4));
    oBinaryTree.AddNode("zaza", std::pair<short, size_t>(3, 7));

    oBinaryTree.PrintPostOrder();*/

    return 0;
}