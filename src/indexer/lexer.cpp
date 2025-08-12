#include <cstdint>
#include <cstdlib>
#include <string>

#include "indexer/lexer.hpp"

namespace lex {

Position::Position() {
  index_m = 0;
  line_m = 1;
  column_m = 1;
}

Position::Position(size_t index, uint32_t line, uint32_t column) :  
  index_m(index), line_m(line), column_m(column) {}

size_t Position::GetIndex() const {
  return index_m;
}

uint32_t Position::GetLine() const {
  return line_m;
}

uint32_t Position::GetColumn() const {
  return column_m;
}


Location::Location() = default;

Location::Location(const std::string& filepath, const Position& start,
    const Position& end) : filepath_m(filepath), start_m(start), end_m(end) {}

std::string Location::GetFilepath() const {
  return filepath_m;
}

Position Location::GetStartPosition() const {
  return start_m;
}

Position Location::GetEndPosition() const {
  return end_m;
}


Token::Token() : kind_m(TokenKind::INVALID), text_m({}), location_m({}) {}

Token::Token(const std::string& text,
    const Location& location) : text_m(text), location_m(location) {};

} // namespace lex ends
