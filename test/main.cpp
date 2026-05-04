#include <cmath>
#include <locale>
#include <cstdio>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <Magick++.h>
#include <sys/ioctl.h>

#define quant(q) (int)(((float)q.redQuantum() / (1 << QuantumDepth)) * 255) << ";" << (int)(((float)q.greenQuantum() / (1 << QuantumDepth)) * 255) << ";"<<  (int)(((float)q.blueQuantum() / (1 << QuantumDepth)) * 255)

int main(int argc, char **argv) {
    std::setlocale(LC_ALL, "");
    using namespace Magick;
    InitializeMagickSentinel sent(*argv);

    Image img;
    img.quiet(false);
    img.read(argv[1]);
    img.scale(Geometry(128, 128));
    img.write("out.png");
    img.modifyImage();

    Pixels view(img);
    unsigned int rows = img.rows();
    unsigned int cols = img.columns();
    auto *pck = view.get(0, 0, cols, rows);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int wrow = w.ws_row * 2;
    int wcol = w.ws_col * 2;
    int maxy = (std::min(wrow, static_cast<int>(rows)) / 2) * 2;
    int maxx = (std::min(wcol, static_cast<int>(cols)) / 2) * 2;
    std::ostringstream buf;
    for (int y = 0; y < maxy; y += 2) {
        for (int x = 0; x < maxx; x++) {
            Color top = img.pixelColor(x, y);
            Color bot = img.pixelColor(x, y);
            std::cout << top.redQuantum() << " ";
            buf << "\x1b[38;2;"
                << quant(top)
                << ";48;2;"
                << quant(bot)
                << ";m▀";
        }
        buf << "\n";
    }
    std::cout << buf.str() << std::endl;

    return 0;
} 