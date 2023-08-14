#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

namespace c_style
{

// declaration
string find_n_replace(string str_i, string str_f, string str_r);
const char *find_n_replace(const char *str_i, const char *str_f, const char *str_r);

// helper functions
void str_append(const char *src, const char *dst, size_t len)
{
  dst = (const char *)malloc(len);
  memcpy((void *)src, (void *)dst, len);
}

size_t str_find(const char *str_i, const char *str_f, size_t init_len)
{
  size_t found_pos = (strstr(str_i, str_f) - str_i + init_len);
  cout << "found_pos: " << found_pos << endl;
  return found_pos;
}

// implementation
string find_n_replace(string str_i, string str_f, string str_r)
{
  string str_o;
  str_o = string(c_style::find_n_replace(str_i.c_str(), str_f.c_str(), str_r.c_str()));
  return str_o;
}

const char *find_n_replace(const char *str_i, const char *str_f, const char *str_r)
{
  const char *str_o = NULL;

  size_t str_i_consumed_len = 0;
  size_t sub_pos = str_find(str_i, str_f, str_i_consumed_len);
  if (0 != sub_pos)
  {
    size_t str_f_len = strlen(str_f);
    size_t str_r_len = strlen(str_r);
    size_t str_i_cur_pos = 0;
    size_t str_o_cur_pos = 0;
    do
    {
      //cout << endl << "sub_pos: " << sub_pos << endl << endl;

      // append the string before str_f from str_i
      //str_o.append(str_i, str_i_cur_pos, (sub_pos - str_i_cur_pos));
      str_append(str_i + str_i_cur_pos, str_o + str_o_cur_pos, (sub_pos - str_i_cur_pos));
      str_o_cur_pos += (sub_pos - str_i_cur_pos);
      //cout << "str_o: " << str_o << endl;

      // append the string str_f at sub_pos
      //str_o.append(str_r);
      str_append(str_o + str_o_cur_pos, str_r, str_r_len);
      str_o_cur_pos += str_r_len;
      //cout << "str_o: " << str_o << endl;

      // update string pos's
      //str_i_cur_pos = sub_pos + str_f.size();
      str_i_cur_pos += sub_pos + str_f_len;
      str_i_consumed_len = str_i_cur_pos;
      //cout << "str_i_cur_pos: " << str_i_cur_pos << endl;

      //sub_pos = str_i.find(str_f, str_i_cur_pos);
      sub_pos = str_find(str_i + str_i_cur_pos, str_f, str_i_consumed_len);
    } while (0 != sub_pos);
  }
  else
  {
    str_o = str_i;
  }

  return str_o;
}

} // namespace c_style

namespace cpp_style
{
// implementation
string find_n_replace(std::string subject, const std::string &search,
                      const std::string &replace)
{
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos)
  {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return subject;
}

} // namespace cpp_style

int main(int a, char **v)
{
  string str_i("I am happy, am.");
  string str_f("am");
  string str_r("men");

  // TODO resolve seg fault
  //string c_str_o(c_style::find_n_replace(str_i, str_f, str_r));
  //std::cout << "c_str_o: [" << c_str_o << "]" << std::endl;

  string cpp_str_o(cpp_style::find_n_replace(str_i, str_f, str_r));
  std::cout << "cpp_str_o: [" << cpp_str_o << "]" << std::endl;
}
