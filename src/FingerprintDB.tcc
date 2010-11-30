template <typename T> T trim(std::string& s) {
    T trimmed_number;

    // trim all after the first ";" and convert it to a stream
    std::istringstream stream(s.substr(0, s.find_first_of(";")));
    // convert the number to an int or float
    stream >> trimmed_number;
    // delete the trimmed number from the string
    s.erase(0, s.find_first_of(";") + 1);

    return trimmed_number;
}
    
