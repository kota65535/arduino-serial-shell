#include <Arduino.h>
#include <pnew.cpp>
#include <serstream>
#include <iterator>
#include <vector>
#include "SerialShell.h"
#include "SerialShellTest.h"

// 定義済みのHardwareSerialインスタンスのSerialを使って初期化
std::ohserialstream serout(Serial);
std::ihserialstream serin(Serial);

SerialShell* shell;

void setup()
{
    Serial.begin(9600);
    // 入出力シリアルストリームクラスの参照で初期化
    shell = new SerialShell(&serout, &serin);
}

void loop()
{
    int ret;
    std::vector<std::string> args;  // コマンド引数のリスト

    // コマンド読み取り
    ret = shell->readCommand();
    // ret　>　0 なら有効データあり
    if (ret > 0) {
    	// 引数のリストを表示
        shell->printArgs();
        // 引数のリストをGet
        args = shell->getArgs();
        // 第1引数で処理分岐
        if (args[0] == "hoge") {
            serout << "func hoge" << std::crlf;
        }
        else if (args[0] == "piyo") {
            serout << "func piyo" << std::crlf;
        }
    }
}
