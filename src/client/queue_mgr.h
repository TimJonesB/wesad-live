#ifndef QUEUEMGRH
#define QUEUEMGRH

template<size_t ConfigIndex>
using DataQueue = boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>>;

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

template <size_t ConfigIndex>
inline bool QueueMgr<ConfigIndex>::empty() {
	return q->empty();
}


template <size_t ConfigIndex>
inline bool QueueMgr<ConfigIndex>::push(std::array<double, ConfigList[ConfigIndex].Nchannels> arr) {
	q->push(arr);
	return true;
}


template <size_t ConfigIndex>
inline bool QueueMgr<ConfigIndex>::pop(std::array<double, ConfigList[ConfigIndex].Nchannels> &arr) {
	q->pop(arr);
	return true;
}

#endif //QUEUEMGRH