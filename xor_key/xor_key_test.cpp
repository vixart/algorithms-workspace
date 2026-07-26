#include "doctest.h"

#include <string>

#include "xor_key.hpp"

TEST_CASE("test #1") {
    std::string handshake = "key";
    std::string ciphertext = "0000005145180811101d040d0e4509190a0d0406160745170412";
    std::string key = algo::find_key(
        3,
        handshake,
        ciphertext
    );
    CHECK(algo::decipher_text(key, ciphertext) == "key: activate protocol now");
}

TEST_CASE("test #2") {
    std::string handshake = "AGENT-HELLO";
    std::string ciphertext = "1274263c67591b762f3e7c4e73550606501c7346101741542156001d411020";
    std::string key = algo::find_key(
        6,
        handshake,
        ciphertext
    );

    CHECK(algo::decipher_text(key, ciphertext) == "AGENT-HELLO: fetch user records");
    CHECK(algo::decipher_text(key, "1274263c67591b762f3e7c4e73561011521832470652471b7352071f5a1a") == "AGENT-HELLO: escalate to admin");
    CHECK(algo::decipher_text(key, "1274263c67591b762f3e7c4e73561b145a18274102065654275b06525715275201134011") == "AGENT-HELLO: exfiltrate the database");
}

