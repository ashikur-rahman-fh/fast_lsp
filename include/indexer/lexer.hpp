#ifndef INDEXER_LEXER_HPP
#define INDEXER_LEXER_HPP

#include <cstdint>
#include <cstdlib>
#include <string>

namespace lex {

class Position {
public:
  Position();
  
  Position(size_t index, uint32_t line, uint32_t column);

  size_t GetIndex() const;

  uint32_t GetLine() const;

  uint32_t GetColumn() const;

private:
  size_t index_m;     // absolute byte index
  uint32_t line_m;    // line number in the file
  uint32_t column_m;  // column number in the file
};

class Location {
public:
  Location();

  Location(const std::string& filepath, const Position& start, const Position& end);

  std::string GetFilepath() const;

  Position GetStartPosition() const;

  Position GetEndPosition() const;

private:
  std::string filepath_m;
  Position start_m;
  Position end_m;
};

enum TokenKind: uint16_t {
  INVALID,
  END_OF_FIND,

  INDENTIFIER,
  KEYWORD,
  
  INTEGER_LITERAL,
  FLOATING_LITERAL,
  CHAR_LITERAL,
  STRING_LITERAL,

  PREPROCESSOR,

  OPERATOR,
  PUNCTUATION,

  COMMENT,
  WHITESPACE,
  RAW
};

class Token {
public:
  Token();

  Token(const std::string& text, const Location& location);
  
  std::string GetText() const;

  Location GetLocation() const;

  bool is(TokenKind kind) const;

private:
  TokenKind kind_m = TokenKind::INVALID;
  std::string text_m;
  Location location_m;
};

} // namespace lex ends

#endif
