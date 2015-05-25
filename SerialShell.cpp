#include <Arduino.h>
#include <serstream>
#include <iterator>
#include <vector>
#include <string>
#include "SerialShell.h"

SerialShell::SerialShell(std::ohserialstream* serout, std::ihserialstream* serin) :
        serout(*serout), serin(*serin), buffer(""), args(0), is_prompting(false) {

}

SerialShell::~SerialShell() {
}

// コマンドの引数を表示する
void SerialShell::printArgs() {
    serout << args.size() << " args: ";
    for (std::vector<std::string>::iterator it = args.begin(); it < args.end(); ++it) {
        serout << *it;
        if (it < args.end() - 1) {
            serout << ", ";
        }
    }
    serout << std::crlf;
}

// コマンドの引数のリストを返す
std::vector<std::string> SerialShell::getArgs() {
    return args;
}

// コマンドを読み込む。
int SerialShell::readCommand() {

    char c = 0;

    // プロンプトの表示
    if (!is_prompting) {
        serout << "# ";
        is_prompting = true;
    }

    if (serin.available() > 0) {
        serin.get(c);
        if (c == '\r') {
            // CRをLFで置き換えて、ヌル文字を追加
            buffer += "\n\0";
            // コマンドのパース
            parseCommand();
            // バッファをクリア
            buffer = "";
            // エコーバック
            serout << std::crlf;
            is_prompting = false;
            return 1;
        }
        else {
            // バッファに追加
            buffer += c;
            // エコーバック
            serout << c;
            return 0;
        }
    }
    else {
        return -1;
    }
}

void SerialShell::parseCommand() {

    unsigned int start = 0, end = 0;

    args.clear();
    while (end < buffer.length()) {
        start = buffer.find_first_not_of(" \t\n", end);
        end = buffer.find_first_of(" \t\n", start);
        if (end - start > 0) {
            args.push_back(buffer.substr(start, end - start));
        }
    }
}
