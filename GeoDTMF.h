const char SEPARATOR = '#';

String addBBetweenConsecutiveDuplicates(const String& str) {
    String result = "";
    char chars[str.length() + 1];
    str.toCharArray(chars, str.length() + 1);    
    for (int i = 0; i < str.length(); i++) {
        result += chars[i];
        if (i < str.length() - 1 && chars[i] == chars[i + 1]) {
            result += 'B';
        }
    }
    return result;
}
    
String encodeDTMF(float latitude, float longitude) {
    String delimiter = "A";  // DTMF-compatible delimiter
    long latInt = round(abs(latitude) * 1e6);
    long lonInt = round(abs(longitude) * 1e6);
    String latPrefix = (latitude < 0) ? "1" : "0";
    String lonPrefix = (longitude < 0) ? "1" : "0";
    String messageBody = latPrefix + String(latInt) + delimiter + lonPrefix + String(lonInt);    
    String encodedMsg = "*" + addBBetweenConsecutiveDuplicates(messageBody) + "#";
    return encodedMsg;
}
