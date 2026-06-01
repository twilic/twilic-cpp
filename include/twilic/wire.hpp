#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace twilic {

using Buffer = std::vector<uint8_t>;

void encode_varuint(uint64_t value, Buffer& out);
uint64_t encode_zigzag(int64_t value);
int64_t decode_zigzag(uint64_t value);
void encode_bytes(const std::vector<uint8_t>& data, Buffer& out);
void encode_string(const std::string& value, Buffer& out);
void encode_bitmap(const std::vector<bool>& bits, Buffer& out);

class Reader {
 public:
  explicit Reader(const std::vector<uint8_t>& input);
  size_t position() const;
  bool is_eof() const;
  uint8_t read_u8();
  std::vector<uint8_t> read_exact(size_t n);
  uint64_t read_varuint();
  int64_t read_i64_zigzag();
  std::vector<uint8_t> read_bytes();
  std::string read_string();
  std::vector<bool> read_bitmap();

 private:
  const std::vector<uint8_t>& input_;
  size_t offset_{0};
};

Reader new_reader(const std::vector<uint8_t>& input);
uint64_t read_u64_le(Reader& reader);
double read_f64_le(Reader& reader);
void append_u64_le(Buffer& out, uint64_t v);
void append_f64_le(Buffer& out, double v);

}  // namespace twilic
