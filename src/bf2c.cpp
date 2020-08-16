#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

enum Token {
  PTR_INC,
  PTR_DEC,
  VAL_INC,
  VAL_DEC,
  OUTPUT,
  INPUT,
  LOOP_START,
  LOOP_END
};

std::vector<uint8_t> read_stdin() {
  std::vector<uint8_t> characters;
  for (std::string line; std::getline(std::cin, line);) {
    for (const auto &c : line) {
      characters.push_back(c);
    }
  }
  return characters;
}

std::vector<Token> to_tokens(std::vector<uint8_t> characters) {
  std::vector<Token> tokens;
  for (const auto &c : characters) {
    switch (c) {
    case '>':
      tokens.push_back(Token::PTR_INC);
      break;
    case '<':
      tokens.push_back(Token::PTR_DEC);
      break;
    case '+':
      tokens.push_back(Token::VAL_INC);
      break;
    case '-':
      tokens.push_back(Token::VAL_DEC);
      break;
    case '.':
      tokens.push_back(Token::OUTPUT);
      break;
    case ',':
      tokens.push_back(Token::INPUT);
      break;
    case '[':
      tokens.push_back(Token::LOOP_START);
      break;
    case ']':
      tokens.push_back(Token::LOOP_END);
      break;
    }
  }
  return tokens;
}

std::vector<std::string> tokens2c(std::vector<Token> tokens) {
  std::vector<std::string> code;

  code.push_back("#include <stdint.h>");
  code.push_back("#include <stdlib.h>");
  code.push_back("#include <stdio.h>");
  code.push_back("int main(int argc, char *argv[]){");
  code.push_back("uint8_t arr[3000] = { 0 };");
  code.push_back("int in = 0;");
  code.push_back("uint16_t ptr = 0;");

  for (const auto &token : tokens) {
    switch (token) {
    case Token::PTR_INC:
      code.push_back("ptr++;");
      break;
    case Token::PTR_DEC:
      code.push_back("ptr--;");
      break;
    case Token::VAL_INC:
      code.push_back("arr[ptr]++;");
      break;
    case Token::VAL_DEC:
      code.push_back("arr[ptr]--;");
      break;
    case Token::OUTPUT:
      code.push_back("printf(\"%c\", arr[ptr]);");
      break;
    case Token::INPUT:
      code.push_back("while ((in = getchar()) != EOF) {");
      code.push_back("if (in == '\\n') break;");
      code.push_back("arr[ptr] = in;");
      code.push_back("}");
      break;
    case Token::LOOP_START:
      code.push_back("while(arr[ptr] > 0){");
      break;
    case Token::LOOP_END:
      code.push_back("}");
      break;
    }
  }

  code.push_back("return EXIT_SUCCESS;}");

  return code;
}

int main(int argc, char *argv[]) {

  auto characters = read_stdin();
  auto tokens = to_tokens(characters);
  auto output = tokens2c(tokens);

  for (auto const &line : output) {
    std::cout << line << "\n";
  }

  return EXIT_SUCCESS;
}
