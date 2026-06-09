#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class Email{

  private:

    int n_links;
    int n_caps;
    float frec_spam_words;
    int len;
    bool has_attachment;
    int n_exclamation;
    bool is_reply;
    bool label;  // 1 = spam, 0 = dfl

  public:

    Email() : n_links(0), n_caps(0), frec_spam_words(0), len(0), has_attachment(0), n_exclamation(0), is_reply(0), label(0) {}

    void buildFromCSV(
      std::string n_links_str, std::string n_caps_str, std::string frec_spam_str, std::string len_str, std::string has_att_str, std::string n_excl_str, std::string is_reply_str, std::string label_str
    ) {

      n_links = std::stoi(n_links_str);
      n_caps = std::stoi(n_caps_str);
      n_exclamation = std::stoi(n_excl_str);
      len = std::stoi(len_str);
      frec_spam_words = std::stof(frec_spam_str);
      has_attachment = std::stoi(has_att_str);
      is_reply = std::stoi(is_reply_str);
      label = std::stoi(label_str);

    }

    int getLinks() const { return n_links; }
    int getCaps() const { return n_caps; }
    float getFreqSpam() const { return frec_spam_words; }
    int getLen() const { return len; }
    bool getAttachment() const { return has_attachment; }
    int getExclamation() const { return n_exclamation; }
    bool getReply() const { return is_reply; }
    bool getLabel() const { return label; }

};

/*
* Function to read the emails from the CSV
*/
std::vector<Email> readEmailsCSV(const std::string& filename);

/*
* Function to get the upper and lower limit of each email tag
*/
std::vector<std::pair<double,double>> maxMinValuesEmail(std::vector<Email> emails);

/*
* Function to normalize each row of the emails
* Values go from 0 to 1 using ( x - min / max - min )
*/
std::vector<double> normalizeEmailLine(
  Email email,
  std::vector<std::pair<double,double>> limits
);

/*
* Overload operator << for an std::vector<T>
*/
template <class T>
std::ostream& operator<<(
  std::ostream& out,
  const std::vector<T>& vector
){

  out << "[ ";

  if( !vector.empty() ){

    out << vector[0];
    for( size_t i{1} ; i < vector.size() ; ++i ){
      out << " , " << vector[i];
    }

  }

  out << " ]";
  return out;
}

#endif