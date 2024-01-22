/// Darts Calculator

#include <vector>
#include <algorithm>

constexpr auto BULL = 50;
constexpr auto OUTER = 25;

constexpr std::vector<int> Range(int start, int end, int step=1 ) {
	std::vector<int> result{};
	for( int i = start; i < end; i += step)
	{
		result.push_back(i);
	}
	return result;
}

constexpr std::vector<int> ReversedRange(int start, int end, int step=1)
{
	std::vector<int> result{};
	for(int i = end; start > i; i -= step)
	{
		result.push_back(i);
	}
	return result;
}

template <typename T>
constexpr std::vector<T> CombineVectors(const std::vector<T>& first, const std::vector<T>& second) {
    return {};
}

template <typename T>
constexpr std::vector<T> CombineVectorsNoDuplicated(const std::vector<T>& first, const std::vector<T>& second) {
    // We assume there are no duplicates in either vector.
    const auto& biggerVector = (first.size() > second.size()) ?  first : second;
    const auto& smallerVector = (first.size() <= second.size()) ?  first : second;
    std::vector<T> result = biggerVector;
    for (const auto item : smallerVector)
    {
        const bool inBoth = std::binary_search(biggerVector.begin(), biggerVector.end(), item);
        if (!inBoth) {
            result.push_back(item);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

constexpr auto singles = ReversedRange(1, 21);
constexpr auto doubles = ReversedRange(2, 41, 2);
constexpr auto triples = ReversedRange(3, 61, 3);
constexpr auto possibles = 
    CombineVectorsNoDuplicated(
        CombineVectorsNoDuplicated(singles, doubles), triples
        );

template <typename Number>
constexpr Number SumAll(const std::vector<Number>& toSum)
{
	Number total = 0;
	for(const Number& a : toSum)
	{
		total += a;
	}
	return total;
}

int max_checkout(int num_darts)
{
	return BULL + 60 * (num_darts - 1);
}

static std::vector<std::vector<int>> Checkouts{};

void lets_play_darts()
{
	for (const auto score : doubles)
	{
		lets_play_darts(score, 1);
	}
	lets_play_darts(BULL, 1);
}

void lets_play_darts(std::vector<int>& current, const int dart=0){
	 int total = 0;
	 if (total = SumAll(current) == target){
		Checkouts.push_back(current);
		return;
	}
	if (total > target || dart == max_darts){
		return;
	}
    std::vector<int> temp{current};
	for (const auto score : possibles){
        temp.push_back(score);
		lets_play_darts(temp, dart+1);
	}
}

void lets_play_darts(const int current, const int dart = 0)
{
	if (current == target) {
		Checkouts.push_back({current});
		return;
	}
	if (current > target || dart == max_darts) {
		return;
	}
	lets_play_darts();
}

void check_me_out(int target, int max_darts){
    lets_play_darts();
    return ;
}

void FredsThingAtTheEnd() {
	constexpr int NUM_DARTS = 4;
	constexpr auto targets = Range(2, max_checkout(NUM_DARTS) + 1);
	
	for (const int target : targets)
	{
		check_me_out(target, NUM_DARTS);
	}
}
