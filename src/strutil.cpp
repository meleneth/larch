#include <iostream>  // I/O 
#include <fstream>   // file I/O
#include <sstream>
#include <iomanip>
#include <math.h>

#include "strutil.hpp"

using namespace Larch;
void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ")
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

std::string bitviz(unsigned int showme)
{
    unsigned int i;
    std::string res('-', 32);

    for(i = 0; i<32 ; i++){
        res[i] = (showme & (1<<i)) ? '1' : '0';
    }
    return res;
}

std::string trimmed(std::string shaggy)
{
    unsigned int start = 0;
    unsigned int end = shaggy.length() -1;
    while(is_whitespace(shaggy[start]) && start < end){
        start++;
    }
    while(is_whitespace(shaggy[end]) && start < end){
        end--;
    }

    return shaggy.substr(start, end-1);
}

unsigned int is_whitespace(char c)
{
    switch(c){
        case ' ':
        case '\t':
            return 1;
        default:
        return 0;
    }
}

std::string get_crc_32(std::string process_me)
{
    static int generated_table = 0;
    static unsigned int CRC32Table[256];

    if(!generated_table){
        generate_crc_table(CRC32Table);
        generated_table = 1;
    }

    unsigned int max_no = process_me.length();
    unsigned int CRC = 0;

    for(unsigned int i=0; i<max_no; i++){
        CRC = (CRC >> 8 )^ CRC32Table[ process_me[i] ^ (( CRC ) & 0x000000FF )];
    }

    std::stringstream result;
    result << std::hex << CRC;
    return result.str();
}

void generate_crc_table(unsigned int *table)
{
    unsigned int Polynomial = 0xEDB88320;
    unsigned int CRC;

    for(int i = 0; i < 256; i++){
        CRC = i;
        for(int j = 8; j > 0; j--) {
            if(CRC & 1){
                CRC = (CRC >> 1) ^ Polynomial;
            } else {
                CRC >>= 1;
            }
        }
        *(table + i)= CRC;
    }
}

std::string replace_all_substrings(std::string from_me, std::string take_me, std::string for_me)
{
    size_t s = from_me.find(take_me);
    unsigned int t_length = take_me.length();
    while(s < std::string::npos){
        from_me.replace(s, t_length, for_me);
        s=from_me.find(take_me);
    }
    return from_me;
}

std::string replace_substrings(std::string from_me, std::string take_me, std::string for_me)
{
    std::string result;

    size_t s = from_me.find(take_me);
    unsigned int t_length = take_me.length();
    while(s < std::string::npos){
        result += (from_me.substr(0, s) + for_me);
        from_me.replace(0, s + t_length, "");
        s=from_me.find(take_me);
    }
    return result + from_me;
}

std::string xml_escape(std::string escape_me)
{
    escape_me = replace_substrings(escape_me, "&", "&amp;");
    escape_me = replace_substrings(escape_me, "\"", "&x22;");
    escape_me = replace_substrings(escape_me, "<", "&lt;");
    return replace_substrings(escape_me, ">", "&gt;");
}

std::string xml_unescape(std::string unescape_me)
{
    unescape_me = replace_substrings(unescape_me, "&x22;", "\"");
    unescape_me = replace_substrings(unescape_me, "&gt;", ">");
    unescape_me = replace_substrings(unescape_me, "&lt;", "<");
    return replace_substrings(unescape_me, "&amp;", "&");
}

std::string js_escape(std::string escape_me)
{
    return replace_substrings(replace_substrings(escape_me, "\\", "\\\\"), "'", "\\'");
}

std::string safe_dirname(std::string unsafe)
{
    std::string s = unsafe;
    unsigned int max_no = s.length();
    unsigned int is_unsafe;
    for(unsigned int i=0; i<max_no; ++i){
        is_unsafe = 1;
        if(s[i] >= 'a' && s[i] <= 'z')
            is_unsafe = 0;
        if(s[i] >= 'A' && s[i] <= 'Z')
            is_unsafe = 0;
        if(is_unsafe)
            s[i] = '_';
    }

    size_t x = s.find("__");
    while(x < std::string::npos){
        s.replace(x, 2, "_");
        x=s.find("__");
    }
    return s;
}

std::string human_readable_bytes(unsigned long long int num_bytes)
{
    std::stringstream result;

    unsigned long long int Kay  = static_cast<unsigned long long int>(pow(2, 10));
    unsigned long long int Mega = static_cast<unsigned long long int>(pow(2, 20));
    unsigned long long int Giga = static_cast<unsigned long long int>(pow(2, 30));

    if(num_bytes < 1)
        return "0b";

    //result << setprecision(2);

    if(num_bytes > Giga) {
        double bytes = num_bytes/Giga;
        bytes = trunc(bytes * 10) / 10;
        result << bytes << "GB";
    } else if (num_bytes > Mega) {
        result << trunc(num_bytes / Mega) << "MB";
    } else {
        result << trunc(num_bytes / Kay) << "kB";
    }
    
    return result.str();
}

std::string file_extension(std::string filename)
{
    if(filename.size() < 4)
        return "";
    std::vector<std::string> pieces;

    Larch::Tokenize(filename, pieces, ".");
    unsigned int num = pieces.size() -1;
    return pieces[num];
}

