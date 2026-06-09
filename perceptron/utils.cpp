#include "utils.hpp"

/*
* Function to read the emails from the CSV
*/
std::vector<Email> readEmailsCSV(const std::string& filename){

  std::vector<Email> emails;
  std::ifstream file(filename);

  if(!file.is_open()){

    std::cerr << "Failed to open the file: " << filename << std::endl;
    return emails;

  }

    std::string currLine;
    std::getline(file, currLine); //skip tags

    while(std::getline(file, currLine)){

      std::stringstream ss(currLine);

      std::string n_links_str, n_caps_str, frec_spam_str, len_str, has_att_str, n_excl_str, is_reply_str, label_str;

      Email email;

      if(
        std::getline(ss, n_links_str, ',') &&
        std::getline(ss, n_caps_str, ',') &&
        std::getline(ss, frec_spam_str, ',') &&
        std::getline(ss, len_str, ',') &&
        std::getline(ss, has_att_str, ',') &&
        std::getline(ss, n_excl_str, ',') &&
        std::getline(ss, is_reply_str, ',') &&
        std::getline(ss, label_str, ',')
      ){

        email.buildFromCSV(n_links_str, n_caps_str, frec_spam_str, len_str, has_att_str, n_excl_str, is_reply_str, label_str);

        emails.push_back(email);

      }

    }

    file.close();
    return emails;

  }

/*
* Function to get the upper and lower limit of each email tag
*/
std::vector<std::pair<double,double>> maxMinValuesEmail(std::vector<Email> emails){

    // { max , min }

    std::pair<double,double> links = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()};
    std::pair<double,double> caps = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()};
    std::pair<double,double> frec = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()};
    std::pair<double,double> len = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()};
    std::pair<double,double> excl = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()};

    for(const Email &email : emails){

        double curr_n_links = email.getLinks();
        double curr_n_caps = email.getCaps();
        double curr_frec = email.getFreqSpam();
        double curr_len = email.getLen();
        double curr_excl = email.getExclamation();

        links.first = std::max(links.first, curr_n_links);
        caps.first = std::max(caps.first, curr_n_caps);
        frec.first = std::max(frec.first, curr_frec);
        len.first = std::max(len.first, curr_len);
        excl.first = std::max(excl.first, curr_excl);

        links.second = std::min(links.second, curr_n_links);
        caps.second = std::min(caps.second, curr_n_caps);
        frec.second = std::min(frec.second, curr_frec);
        len.second = std::min(len.second, curr_len);
        excl.second = std::min(excl.second, curr_excl);
    }

    return {links, caps, frec, len, excl};
}

/*
* Function to normalize each row of the emails
* Values go from 0 to 1 using ( x - min / max - min )
*/
std::vector<double> normalizeEmailLine(
  Email email,
  std::vector<std::pair<double,double>> limits
){

  // Normalize function
  auto N = [](double min, double max, int val) { return static_cast<double>( (val - min) / (max - min) ); };

  double links = N( limits[0].second, limits[0].first, email.getLinks() );
  double caps = N( limits[1].second, limits[1].first, email.getCaps() );
  double frec = N( limits[2].second, limits[2].first, email.getFreqSpam() );
  double len = N( limits[3].second, limits[3].first, email.getLen());
  double has_attachment = static_cast<double>(email.getAttachment());
  double excl = N( limits[4].second, limits[4].first, email.getExclamation());
  double reply = static_cast<double>(email.getReply());
  double label = static_cast<double>(email.getLabel());

  return {links, caps, frec, len, has_attachment, excl, reply, label};

}