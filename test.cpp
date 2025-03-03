// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNullTest)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreateTest)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFailTest)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVectorTest)
{
    // is the collection empty?
    // if empty, the size must be 0
	EXPECT_TRUE(collection->empty()); // Expects that the collection is empty
	ASSERT_EQ(collection->size(), 0); // Asserts that the size of the collection is 0 since it is empty
    add_entries(1); // Adds 1 entry to the collection
	EXPECT_EQ(collection->size(), 1); // Expects that the collections size now includes the 1 added entry
	EXPECT_FALSE(collection->empty()); // If we are already expecting there to be 1 entry we want to ensure that the collection is only empty when size is 0 and the size and empty are noted

    // is the collection still empty?
    // if not empty, what must the size be? The size must be equal to 1 since we added an entry and the collection was previously empty
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVectorTest)
{
    add_entries(5);
	ASSERT_EQ(collection->size(), 5); // Asserts that the size of the collection is now equal to 5
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanOrEqualToSizeTest)
{
	EXPECT_GE(collection->max_size(), collection->size()); // Test that asserts that the max size of the collection is greater than the current size of the collection for 0 entries
	add_entries(1); // Adds 1 entry to the collection
	EXPECT_GE(collection->max_size(), collection->size()); // Test that asserts that the max size of the collection is greater than the current size of the collection for 1 entry
	collection->clear(); // Clears the collection
    add_entries(5); // Adds 5 entries to the collection
	EXPECT_GE(collection->max_size(), collection->size()); // Test that asserts that the max size of the collection is greater than the current size of the collection for 5 entries
	collection->clear(); // Clears the collection
    add_entries(10); // Adds 10 entries to the collection
	EXPECT_GE(collection->max_size(), collection->size()); // Test that asserts that the max size of the collection is greater than the current size of the collection for 10 entries
}
// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanOrEqualToSizeTest)
{
	EXPECT_GE(collection->capacity(), collection->size()); // Test that expects that the capacity of the collection to be greater than or equal to the current size of the collection for 0 entries uses expect to take not of result and continue
	add_entries(1); // Adds 1 entry to the collection
	EXPECT_GE(collection->capacity(), collection->size()); // Test that expects that the capacity of the collection to be greater than or equal to the current size of the collection for 1 entry uses expect to take not of result and continue
	collection->clear(); // Clears the collection
    add_entries(5); // Adds 5 entries to the collection
	EXPECT_GE(collection->capacity(), collection->size()); // Test that expects that the capacity of the collection to be greater than or equal to the current size of the collection for 5 entries uses expect to take not of result and continue
	collection->clear(); // Clears the collection
	add_entries(10); // Adds 10 entries to the collection
	EXPECT_GE(collection->capacity(), collection->size()); // Test that expects that the capacity of the collection to be greater than or equal to the current size of the collection for 10 entries uses expect to take not of result and continue
}
// TODO: Create a test to verify resizing increases the collection
// Alternative solution to the test below is asserting that its true that the collection size after resizing is greater than the current size stored before
TEST_F(CollectionTest, ResizeIncreaseCollectionTest)
{
	add_entries(5); // Adds 5 entries to the collection
	auto currentSize = collection->size(); // Saves the curren size of the collection (which should be 5) to a variable currentSize
	collection->resize(currentSize + 5); // Resizes the collection using resize to increase its size by 5
	ASSERT_EQ(collection->size(), currentSize + 5); // Test that asserts the collections size is currently equal to the currentSize + 5 demonstarting a collection increase
}

// TODO: Create a test to verify resizing decreases the collection
// Alternative solution to the test below is asserting that its true that the collection size after resizing is less than the current size stored before
TEST_F(CollectionTest, ResizeDecreaseCollectionTest)
{
	add_entries(15); // Adds 15 entries to the collection
	auto currentSize = collection->size(); // Saves the current size of the collection (which should be 15) to a variable currentSize
	collection->resize(currentSize - 5); // Resizes the collection using resize to decrease its size by 5
	ASSERT_EQ(collection->size(), currentSize - 5); // Test that asserts the collections size is currently equal to the currentSize - 5 demonstarting a collection decrease
}

// TODO: Create a test to verify resizing decreases the collection to zero
// Alternative solution to the test below is asserting that the size is == to 0 and asserting true
TEST_F(CollectionTest, ResizeDecreaseToZeroCollectionTest)
{
	add_entries(20); // Adds 20 entries to the collection
	ASSERT_EQ(collection->size(), 20); // Although this may seem redundant and meaningless I like to minimize the chance of unexpected errors and establish that the collection is not zero current
	collection->resize(0); // Resizes the collection using resize to decrease its size from 20 to 0
	ASSERT_EQ(collection->size(), 0); // Test asserting the collection is no longer 20 but has been resized decreasing its size to 0
}

// TODO: Create a test to verify clear erases the collection
// Alternative solution could be like previous alternative of asserting true that the size of the collection is now == 0
TEST_F(CollectionTest, ClearErasesCollectionTest)
{
	add_entries(15); // Adds 15 entries to the collection
	ASSERT_EQ(collection->size(), 15); // Test asserts that the collection has 15 entries after add entries has been called
	collection->clear(); // Clears the collection using the clear method
	ASSERT_EQ(collection->size(), 0); // Asserts that the collection is now empty meaning its size is now equal to 0
}

// TODO: Create a test to verify erase(begin,end) erases the collection
// Alternative solution could be like previous alternative of asserting true that the size of the collection is now == 0
TEST_F(CollectionTest, EraseBeginEndCollectionTest)
{
	add_entries(10); // Adds 10 entries to the collection
	ASSERT_EQ(collection->size(), 10); // Test asserts that the collection has 10 entries after add entries has been called with value 10
	collection->erase(collection->begin(), collection->end()); // Erases the collection using the erase method with begin and end as parameters
	ASSERT_EQ(collection->size(), 0); // Test asserts that the collection is now empty meaning its size is now equal to 0 erasing its contents from begining to end
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
// Alternative solution is asserting true that the capacity is greater than the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSizeTest)
{
	add_entries(15); // Adds 15 entries to the collection
	auto currentSize = collection->size(); // Saves the current size of the collection (which should be 15) to a variable currentSize
	auto currentCapacity = collection->capacity(); // Saves the current capacity of the collection to a variable currentCapacity
	collection->reserve(currentCapacity + 15); // Reserves the collection using reserve to increase its capacity by 15
	EXPECT_EQ(collection->size(), currentSize); // Test expects that the collections size is currently equal to the currentSize demonstrating that the size has not changed
	EXPECT_EQ(collection->capacity(), currentCapacity + 15); // Test expects that the collections capacity is currently equal to the currentCapacity + 15 demonstrating that the capacity has increased by 15
	EXPECT_NE(collection->capacity(), currentSize); // Test expects that the collections capacity is not equal to the collections size
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionTest)
{
	add_entries(10); // Adds 10 entries to the collection
	ASSERT_THROW(collection->at(22), std::out_of_range); // Test asserts that an out of range exception is thrown when calling at() with an index out of bounds
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, CollectionReversalTest) { // Tests the reverse functionality of the collection ensuring that the first and last elements are swapped
	add_entries(10); // Adds 10 entries to the collection
	auto firstElement = collection->front(); // Saves the first element of the collection to a variable firstElement
	auto lastElement = collection->back(); // Saves the last element of the collection to a variable lastElement
	std::reverse(collection->begin(), collection->end()); // Reverses the collection using the reverse method
	ASSERT_EQ(collection->front(), lastElement); // Asserts that the first element of the collection is now equal to the last element of the collection
	ASSERT_EQ(collection->back(), firstElement); // Asserts that the last element of the collection is now equal to the first element of the collection
}

TEST_F(CollectionTest, CollectionPushTest) { 
	add_entries(20); // Adds 20 entries to the collection
	auto lastElement = collection->back(); // Saves the last element of the collection to a variable lastElement
	collection->push_back(lastElement+2); // Pushes the last element +2 to the end of the collection
	ASSERT_NE(collection->back(), lastElement); // Asserts that the new last element is not equal to the previous one ensuring push back functionality
	
}

TEST_F(CollectionTest, ResizeDoesNotAllowNegativesTest) { // Tests that the resize method does not allow negative values
	collection->clear(); // Clears the collection
	ASSERT_THROW(collection->resize(-1), std::length_error); // Test asserts that a length error exception is thrown when calling resize with a negative value
	
}


