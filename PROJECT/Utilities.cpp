
#include "Utilities.h"
#include <iostream>
namespace seneca {
    char Utilities::m_delimiter ;

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField =newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

   //extract token changed, space removing added. new version of function: 
   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string token;
        size_t delimiterPos =str.size();

        for (size_t i =next_pos; i<str.size();++i) {
            if (str[i] ==m_delimiter) {
                delimiterPos= i;
                break;}
        }

        if (delimiterPos!= str.size()) {
            token = str.substr(next_pos,delimiterPos -next_pos);
            if (token.empty() ) {
                more =false;
                throw "ERROR: No token.";
            }

            if (token.length()> m_widthField)
                m_widthField =token.length();
            

            next_pos =delimiterPos+ 1;
            more = true;
        } 

        else {
            token = str.substr(next_pos);
            if (token.empty()) {
                more= false;
            }
            if (token.length()> m_widthField)
                m_widthField =token.length();
            more = false;
        }
        size_t startPos = 0;
        while (startPos <token.length()&&std::isspace(token[startPos])) {
            ++startPos;
        }
        size_t endPos =token.length();
        while (endPos> 0&& std::isspace(token[endPos-1])) {
            --endPos;
        }
        token =token.substr(startPos,endPos-startPos);

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter =newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
