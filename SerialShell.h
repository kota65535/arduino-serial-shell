#ifndef _SERIAL_SHELL_
#define _SERIAL_SHELL_

class SerialShell {
private:
    std::ohserialstream& serout;    // 出力用ストリームの参照
    std::ihserialstream& serin;     // 入力用ストリームの参照
    std::string buffer;
    std::vector<std::string> args;
    bool is_prompting;

public:
    SerialShell(std::ohserialstream* serout, std::ihserialstream* serin);
    virtual ~SerialShell();

    int readCommand();
    std::vector<std::string> getArgs();
    void printArgs();

private:
    void parseCommand();
};

#endif /* _SERIAL_SHELL_ */
