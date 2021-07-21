/** @file */
#ifndef QUEUEMGRH
#define QUEUEMGRH

/** 
 * @brief Alias for single producer (Client) and single consumer (processor) queue of arrays of data.
 *
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * Alias for thread safe lock free single producer single consumer queue of std::arrays of size ConfigList[ConfigIndex].Nchannels.
 */
template<size_t ConfigIndex>
using DataQueue = boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>>;


/** 
 * @brief Namespace to hold global DataQueues 
 * Namespace to hold global DataQueue<DataIndex> objects corresponding to each data stream Client.
 */
namespace ClientQueues{
    DataQueue<0> q0 {data_queue_sz};
    DataQueue<1> q1 {data_queue_sz};
    DataQueue<2> q2 {data_queue_sz};
    DataQueue<3> q3 {data_queue_sz};
    DataQueue<4> q4 {data_queue_sz};
    DataQueue<5> q5 {data_queue_sz};
    DataQueue<6> q6 {data_queue_sz};
    DataQueue<7> q7 {data_queue_sz};
    DataQueue<8> q8 {data_queue_sz};
    DataQueue<9> q9 {data_queue_sz};
}


/** 
 * @brief Manages global DataQueue collection from ClientQueues.
 *
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * Manages global DataQueue collection by associating DataQueue with its corresponding ConfigIndex and managing the queue's basic operations.
 */
template <size_t ConfigIndex>
class QueueMgr {
public:
	QueueMgr();
    bool empty();
    bool push(std::array<double, ConfigList[ConfigIndex].Nchannels> arr);
    bool pop(std::array<double, ConfigList[ConfigIndex].Nchannels> &arr);
private:

    DataQueue<ConfigIndex> *q = nullptr;

};


/** 
 * @brief Manages global DataQueue collection from ClientQueues.
 *
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * Manages global DataQueue collection by associating DataQueue with its corresponding ConfigIndex and managing the queue's basic operations.
 */
template <size_t ConfigIndex>
inline QueueMgr<ConfigIndex>::QueueMgr(){
	if constexpr(ConfigIndex == 0)
		q = &ClientQueues::q0;
	else if constexpr(ConfigIndex == 1)
		q = &ClientQueues::q1;
	else if constexpr(ConfigIndex == 2)
		q = &ClientQueues::q2;
	else if constexpr(ConfigIndex == 3)
		q = &ClientQueues::q3;
	else if constexpr(ConfigIndex == 4)
		q = &ClientQueues::q4;
	else if constexpr(ConfigIndex == 5)
		q = &ClientQueues::q5;
	else if constexpr(ConfigIndex == 6)
		q = &ClientQueues::q6;
	else if constexpr(ConfigIndex == 7)
		q = &ClientQueues::q7;
	else if constexpr(ConfigIndex == 8)
		q = &ClientQueues::q8;
	else if constexpr(ConfigIndex == 9)
		q = &ClientQueues::q9;
}

/** 
 * @brief Calls DataQueue ptr's empty method.
 *
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @returns True if empty
 */
template <size_t ConfigIndex>
inline bool QueueMgr<ConfigIndex>::empty() {
	return q->empty();
}


/** 
 * @brief Calls DataQueue ptr's push method.
 * @param arr data array to go into DataQueue.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @returns True if successful
 */
template <size_t ConfigIndex>
inline bool QueueMgr<ConfigIndex>::push(std::array<double, ConfigList[ConfigIndex].Nchannels> arr) {
	return q->push(arr);
}


/** 
 * @brief Calls DataQueue ptr's pop(std::array) form of method.
 * @param arr data array reference to copy into.
 * @returns True if successful
 */
template <size_t ConfigIndex>
inline bool QueueMgr<ConfigIndex>::pop(std::array<double, ConfigList[ConfigIndex].Nchannels> &arr) {
	return q->pop(arr);
}

#endif //QUEUEMGRH