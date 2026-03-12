#include <criterion/criterion.h>

#include "../strgPtr.h"

Test(strgLen, counts_regular_string) {
    cr_assert_eq(strgLen("Stony Brook"), 11);
}

Test(strgLen, counts_string_with_space_and_digits) {
    cr_assert_eq(strgLen("CSE 220"), 7);
}

Test(strgLen, counts_single_character) {
    cr_assert_eq(strgLen("C"), 1);
}

Test(strgLen, counts_longer_string) {
    cr_assert_eq(strgLen("System Fundamental"), 18);
}

Test(strgLen, counts_single_digit) {
    cr_assert_eq(strgLen("1"), 1);
}

Test(strgLen, handles_empty_string) {
    cr_assert_eq(strgLen(""), 0);
}

Test(strgLen, rejects_null_pointer) {
    cr_assert_eq(strgLen(NULL), -1);
}

Test(strgLen, counts_mixed_case_text) {
    cr_assert_eq(strgLen("Hello World"), 11);
}

Test(strgLen, counts_numeric_string) {
    cr_assert_eq(strgLen("123456789"), 9);
}

Test(strgLen, counts_lowercase_single_character) {
    cr_assert_eq(strgLen("a"), 1);
}

Test(strgCopy, copies_full_string) {
    char dest[32] = "";

    strgCopy("Computer Science", dest, sizeof(dest));

    cr_assert_str_eq(dest, "Computer Science");
}

Test(strgCopy, copies_string_with_punctuation) {
    char dest[32] = "";

    strgCopy("CSE-220", dest, sizeof(dest));

    cr_assert_str_eq(dest, "CSE-220");
}

Test(strgCopy, truncates_when_destination_is_small) {
    char dest[5] = "xxxx";

    strgCopy("Computer Science", dest, sizeof(dest));

    cr_assert_str_eq(dest, "Comp");
}

Test(strgCopy, copies_single_character) {
    char dest[8] = "";

    strgCopy("1", dest, sizeof(dest));

    cr_assert_str_eq(dest, "1");
}

Test(strgCopy, copies_empty_string) {
    char dest[8] = "hello";

    strgCopy("", dest, sizeof(dest));

    cr_assert_str_eq(dest, "");
}

Test(strgCopy, ignores_null_source) {
    char dest[8] = "test";

    strgCopy(NULL, dest, sizeof(dest));

    cr_assert_str_eq(dest, "test");
}

Test(strgCopy, stores_only_null_when_size_is_one) {
    char dest[1] = {'x'};

    strgCopy("Hello", dest, sizeof(dest));

    cr_assert_str_eq(dest, "");
}

Test(strgCopy, does_nothing_when_size_is_zero) {
    char dest[8] = "test";

    strgCopy("Hello", dest, 0);

    cr_assert_str_eq(dest, "test");
}

Test(strgCopy, copies_exact_fit) {
    char dest[6] = "xxxxx";

    strgCopy("Hello", dest, sizeof(dest));

    cr_assert_str_eq(dest, "Hello");
}

Test(strgCopy, truncates_to_available_bytes) {
    char dest[8] = "zzzzzzz";

    strgCopy("The quick brown fox", dest, sizeof(dest));

    cr_assert_str_eq(dest, "The qui");
}

Test(strgChangeCase, flips_basic_letters) {
    char text[] = "Stony Brook";

    strgChangeCase(text);

    cr_assert_str_eq(text, "sTONY bROOK");
}

Test(strgChangeCase, leaves_digit_adjacent_letters_unchanged) {
    char text[] = "CSE220";

    strgChangeCase(text);

    cr_assert_str_eq(text, "csE220");
}

Test(strgChangeCase, keeps_both_sides_of_digit_unchanged) {
    char text[] = "a1b";

    strgChangeCase(text);

    cr_assert_str_eq(text, "a1b");
}

Test(strgChangeCase, handles_complex_mixture) {
    char text[] = "System Fundamental220";

    strgChangeCase(text);

    cr_assert_str_eq(text, "sYSTEM fUNDAMENTAl220");
}

Test(strgChangeCase, leaves_digit_only_string_unchanged) {
    char text[] = "1";

    strgChangeCase(text);

    cr_assert_str_eq(text, "1");
}

Test(strgChangeCase, handles_empty_string) {
    char text[] = "";

    strgChangeCase(text);

    cr_assert_str_eq(text, "");
}

Test(strgChangeCase, ignores_null_pointer) {
    strgChangeCase(NULL);
    cr_assert(1);
}

Test(strgChangeCase, flips_all_uppercase_letters) {
    char text[] = "HELLO";

    strgChangeCase(text);

    cr_assert_str_eq(text, "hello");
}

Test(strgChangeCase, flips_all_lowercase_letters) {
    char text[] = "hello";

    strgChangeCase(text);

    cr_assert_str_eq(text, "HELLO");
}

Test(strgChangeCase, preserves_punctuation_positions) {
    char text[] = "Hello, World!";

    strgChangeCase(text);

    cr_assert_str_eq(text, "hELLO, wORLD!");
}

Test(strgDiff, returns_negative_one_for_identical_strings) {
    cr_assert_eq(strgDiff("Hello", "Hello"), -1);
}

Test(strgDiff, finds_difference_in_middle) {
    cr_assert_eq(strgDiff("CSE-220", "CSE220"), 3);
}

Test(strgDiff, finds_difference_at_start) {
    cr_assert_eq(strgDiff("CSE220", "SE220"), 0);
}

Test(strgDiff, treats_empty_strings_as_equal) {
    cr_assert_eq(strgDiff("", ""), -1);
}

Test(strgDiff, detects_length_difference_at_null_terminator) {
    cr_assert_eq(strgDiff("abc", "abcd"), 3);
}

Test(strgDiff, rejects_null_first_argument) {
    cr_assert_eq(strgDiff(NULL, "test"), -2);
}

Test(strgDiff, rejects_null_second_argument) {
    cr_assert_eq(strgDiff("test", NULL), -2);
}

Test(strgDiff, handles_empty_vs_nonempty) {
    cr_assert_eq(strgDiff("", "test"), 0);
}

Test(strgDiff, handles_single_character_difference) {
    cr_assert_eq(strgDiff("a", "b"), 0);
}

Test(strgDiff, handles_late_difference) {
    cr_assert_eq(strgDiff("abcdef", "abcdez"), 5);
}

Test(strgInterleave, interleaves_equal_length_strings) {
    char dest[16] = "";

    strgInterleave("abc", "123", dest, sizeof(dest));

    cr_assert_str_eq(dest, "a1b2c3");
}

Test(strgInterleave, appends_remaining_first_string) {
    char dest[16] = "";

    strgInterleave("abcdef", "123", dest, sizeof(dest));

    cr_assert_str_eq(dest, "a1b2c3def");
}

Test(strgInterleave, appends_remaining_second_string) {
    char dest[16] = "";

    strgInterleave("cse", "12345", dest, sizeof(dest));

    cr_assert_str_eq(dest, "c1s2e345");
}

Test(strgInterleave, handles_second_string_shorter) {
    char dest[16] = "";

    strgInterleave("1234", "cs", dest, sizeof(dest));

    cr_assert_str_eq(dest, "1c2s34");
}

Test(strgInterleave, handles_both_empty) {
    char dest[4] = "xx";

    strgInterleave("", "", dest, sizeof(dest));

    cr_assert_str_eq(dest, "");
}

Test(strgInterleave, handles_empty_first_string) {
    char dest[8] = "";

    strgInterleave("", "123", dest, sizeof(dest));

    cr_assert_str_eq(dest, "123");
}

Test(strgInterleave, truncates_to_buffer_size) {
    char dest[5] = "xxxx";

    strgInterleave("abc", "123", dest, sizeof(dest));

    cr_assert_str_eq(dest, "a1b2");
}

Test(strgInterleave, handles_single_character_inputs) {
    char dest[4] = "";

    strgInterleave("a", "1", dest, sizeof(dest));

    cr_assert_str_eq(dest, "a1");
}

Test(strgInterleave, handles_longer_words) {
    char dest[16] = "";

    strgInterleave("hello", "world", dest, sizeof(dest));

    cr_assert_str_eq(dest, "hweolrllod");
}

Test(strgInterleave, ignores_null_input) {
    char dest[8] = "keep";

    strgInterleave(NULL, "123", dest, sizeof(dest));

    cr_assert_str_eq(dest, "keep");
}

Test(strgReverseLetters, reverses_simple_word) {
    char text[] = "Hello";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "olleH");
}

Test(strgReverseLetters, preserves_dash_position) {
    char text[] = "ab-cd";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "dc-ba");
}

Test(strgReverseLetters, preserves_digits) {
    char text[] = "a1b2c";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "c1b2a");
}

Test(strgReverseLetters, handles_empty_string) {
    char text[] = "";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "");
}

Test(strgReverseLetters, handles_single_letter) {
    char text[] = "a";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "a");
}

Test(strgReverseLetters, leaves_nonletters_unchanged) {
    char text[] = "123";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "123");
}

Test(strgReverseLetters, preserves_spaces) {
    char text[] = "a b c";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "c b a");
}

Test(strgReverseLetters, handles_mixed_case_letters) {
    char text[] = "AaBbCc";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "cCbBaA");
}

Test(strgReverseLetters, preserves_punctuation) {
    char text[] = "a,b.c";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "c,b.a");
}

Test(strgReverseLetters, handles_letters_separated_by_digits) {
    char text[] = "Hello123World";

    strgReverseLetters(text);

    cr_assert_str_eq(text, "dlroW123olleH");
}