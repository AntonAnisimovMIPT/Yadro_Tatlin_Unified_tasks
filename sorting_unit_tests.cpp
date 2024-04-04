#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <algorithm>

auto generate_random_uint32() {
    return static_cast<std::uint32_t>(rand());
}

class ExternalSortTest : public ::testing::TestWithParam<int> {};

TEST_P(ExternalSortTest, SortingViaExternalCommand) {

    const int num_elements = GetParam();
    std::vector<std::uint32_t> original_sequence;

    for (int i = 0; i < num_elements; ++i) {
        original_sequence.push_back(generate_random_uint32());
    }

    std::ofstream input_file("input.txt");
    for (const auto& num : original_sequence) {
        input_file << num << std::endl;
    }
    input_file.close();

    auto command = "./engine.sh " + std::to_string(num_elements);
    const char * cmd = command.c_str();
    std::system(cmd);

    std::ifstream output_file("output.txt");
    std::vector<uint32_t> sorted_sequence;
    uint32_t num;
    while (output_file >> num) {
        sorted_sequence.push_back(num);
    }
    output_file.close();

    std::sort(original_sequence.begin(), original_sequence.end());

    // Проверка сортировки
    ASSERT_EQ(original_sequence.size(), sorted_sequence.size());
    for (size_t i = 0; i < original_sequence.size(); ++i) {
        EXPECT_EQ(original_sequence[i], sorted_sequence[i]);
    }

}

// задание значений для размера лент
INSTANTIATE_TEST_SUITE_P(VariousNumElements, ExternalSortTest,
                         ::testing::Values(20, 50, 100, 500, 
                                           1000, 2000, 5000, 
                                           100000, 20000, 50000));

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
