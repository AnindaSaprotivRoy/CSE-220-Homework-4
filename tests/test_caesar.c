#include <criterion/criterion.h>

#include "../cse_caesar.h"

Test(encryptCaesar, encrypts_basic_text) {
    char ciphertext[] = "                ";

    int result = encryptCaesar("abc", ciphertext, 2);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(ciphertext, "ceg__EOM__");
}

Test(encryptCaesar, encrypts_mixed_case_text) {
    char ciphertext[] = "                ";

    int result = encryptCaesar("Ayb", ciphertext, 3);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(ciphertext, "Dcg__EOM__");
}

Test(encryptCaesar, encrypts_letters_and_digits) {
    char ciphertext[] = "                              ";

    int result = encryptCaesar("Cse220", ciphertext, 1);

    cr_assert_eq(result, 6);
    cr_assert_str_eq(ciphertext, "Duh911__EOM__");
}

Test(encryptCaesar, handles_zero_key_with_position_shift) {
    char ciphertext[] = "                ";

    int result = encryptCaesar("CS", ciphertext, 0);

    cr_assert_eq(result, 2);
    cr_assert_str_eq(ciphertext, "CT__EOM__");
}

Test(encryptCaesar, appends_eom_for_empty_plaintext_when_capacity_exists) {
    char ciphertext[] = "                ";

    int result = encryptCaesar("", ciphertext, 5);

    cr_assert_eq(result, 0);
    cr_assert_str_eq(ciphertext, "__EOM__");
}

Test(encryptCaesar, rejects_null_plaintext) {
    char ciphertext[] = "                ";

    cr_assert_eq(encryptCaesar(NULL, ciphertext, 2), -2);
}

Test(encryptCaesar, rejects_null_ciphertext) {
    cr_assert_eq(encryptCaesar("abc", NULL, 2), -2);
}

Test(encryptCaesar, fails_when_capacity_is_empty_string) {
    char ciphertext[] = "";

    cr_assert_eq(encryptCaesar("abc", ciphertext, 2), -1);
}

Test(encryptCaesar, fails_when_capacity_cannot_hold_marker) {
    char ciphertext[] = "abc";

    cr_assert_eq(encryptCaesar("abc", ciphertext, 2), -1);
}

Test(encryptCaesar, wraps_position_aware_shift_for_large_key) {
    char ciphertext[] = "                ";

    int result = encryptCaesar("abc", ciphertext, 26);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(ciphertext, "ace__EOM__");
}

Test(decryptCaesar, decrypts_basic_text) {
    char plaintext[] = "                ";

    int result = decryptCaesar("ceg__EOM__", plaintext, 2);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(plaintext, "abc");
}

Test(decryptCaesar, decrypts_mixed_case_text) {
    char plaintext[] = "                ";

    int result = decryptCaesar("Dcg__EOM__", plaintext, 3);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(plaintext, "Ayb");
}

Test(decryptCaesar, decrypts_letters_and_digits) {
    char plaintext[] = "                              ";

    int result = decryptCaesar("Duh911__EOM__", plaintext, 1);

    cr_assert_eq(result, 6);
    cr_assert_str_eq(plaintext, "Cse220");
}

Test(decryptCaesar, handles_zero_key_with_position_shift) {
    char plaintext[] = "                ";

    int result = decryptCaesar("CT__EOM__", plaintext, 0);

    cr_assert_eq(result, 2);
    cr_assert_str_eq(plaintext, "CS");
}

Test(decryptCaesar, decrypts_empty_payload) {
    char plaintext[] = "                ";

    int result = decryptCaesar("__EOM__", plaintext, 7);

    cr_assert_eq(result, 0);
    cr_assert_str_eq(plaintext, "");
}

Test(decryptCaesar, rejects_null_ciphertext) {
    char plaintext[] = "                ";

    cr_assert_eq(decryptCaesar(NULL, plaintext, 2), -2);
}

Test(decryptCaesar, rejects_null_plaintext) {
    cr_assert_eq(decryptCaesar("ceg__EOM__", NULL, 2), -2);
}

Test(decryptCaesar, returns_zero_for_empty_plaintext_capacity) {
    char plaintext[] = "";

    cr_assert_eq(decryptCaesar("ceg__EOM__", plaintext, 2), 0);
}

Test(decryptCaesar, returns_negative_one_when_eom_is_missing) {
    char plaintext[] = "                ";

    cr_assert_eq(decryptCaesar("abc", plaintext, 2), -1);
}

Test(decryptCaesar, truncates_to_plaintext_capacity_minus_one) {
    char plaintext[] = "xxxx";

    int result = decryptCaesar("Duh911__EOM__", plaintext, 1);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(plaintext, "Cse");
}

Test(decryptCaesar, stops_at_first_eom_marker) {
    char plaintext[] = "                ";

    int result = decryptCaesar("ceg__EOM__junk__EOM__", plaintext, 2);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(plaintext, "abc");
}

Test(decryptCaesar, handles_large_key_round_trip) {
    char plaintext[] = "                ";

    int result = decryptCaesar("ace__EOM__", plaintext, 26);

    cr_assert_eq(result, 3);
    cr_assert_str_eq(plaintext, "abc");
}