
#if !defined(SINGLETON_H_INCLUDED)
#define SINGLETON_H_INCLUDED
#include<cstdio>	//fprintf
#include<cstdlib>	//atexit
#include<new>		//std::bad_alloc
#include<exception>	//std::exception
#include<mutex>		//std::mutex
#pragma warning(disable:4290)
#define TEMPLATE template<typename _STR>
#define TEMPLATE_DEFINE(R)	template<typename _STR> R SingleTon<_STR>

#define CREATE_SINGLETON(CLASS)	struct CLASS : public SingleTonRepository<CLASS>

#define ATTACH(A,B)	A##B
#define CREATE_VALUE(CLASS,TYPE,NAME)\
private:\
	TYPE NAME; \
public:\
	TYPE ATTACH(Get, NAME)() {\
	SingleTon<CLASS>::lock(); \
	TYPE ret = this->NAME; \
	SingleTon<CLASS>::unlock(); \
	return ret; \
	}\
	void ATTACH(Set, NAME)(TYPE&& _NAME) {\
	SingleTon<CLASS>::lock(); \
	this->NAME = _NAME; \
	SingleTon<CLASS>::unlock(); \
	}\
	void ATTACH(Set, NAME)(TYPE& _NAME) {\
	SingleTon<CLASS>::lock(); \
	this->NAME = _NAME; \
	SingleTon<CLASS>::unlock(); \
	}\



using namespace std;
namespace design_pattern{
	TEMPLATE class SingleTon;
	/***
	*	@name : SingleTonRepository
	*	@comment : if use SingleTon, you must be inheritance this class
	*/
	TEMPLATE class SingleTonRepository{
	private:
		static mutex _lock;
	protected:
		SingleTonRepository() {
			if (SingleTonRepository<_STR>::_lock.try_lock()){
				fprintf(stderr, "SingleTonRepository Creating only SingleTon::use() method!\n");
				abort();
			}
		};
		virtual ~SingleTonRepository() {};
	private:
		SingleTonRepository(const SingleTonRepository&) = delete;
		const SingleTonRepository& operator=(const SingleTonRepository&) = delete;
	public:
		friend SingleTon<_STR>;
	};
	TEMPLATE mutex SingleTonRepository<_STR>::_lock = mutex();
	/***
	*	@name : SingleTon
	*	@comment : load repository struct(class) like template, and use Get()
	*	@warning : create(first call Get) , destory(program end)
	*/
	TEMPLATE class SingleTon{
	private:
		static _STR* instance;
		static mutex _mutex;
		SingleTon() = delete;
		~SingleTon() = delete;
		SingleTon(const SingleTon&) = delete;
		const SingleTon& operator=(const SingleTon&) = delete;
		static void Release();
	public:
		static _STR* use() throw(bad_alloc, exception);
		static void lock();
		static void unlock();
		static bool try_lock();
		static _Mutex_base::native_handle_type native_handle();
	};
	TEMPLATE_DEFINE(_STR*)::instance = nullptr;
	TEMPLATE_DEFINE(mutex)::_mutex = mutex();
	/**
	*	@name : Get instance
	*	@comment : double check
	*	@exception : bad_alloc, exception
	*/
	TEMPLATE_DEFINE(_STR*)::use() {
		if (!SingleTon<_STR>::instance){
			SingleTonRepository<_STR>::_lock.lock();
			if (!SingleTon<_STR>::instance){
				SingleTon<_STR>::instance = new _STR;
				SingleTonRepository<_STR>* str = dynamic_cast<SingleTonRepository<_STR>*>(SingleTon<_STR>::instance);
				if (!str){
					SingleTon::Release();
					throw exception("bad inheritance(must inheritance SingleTonRepository)");
				}
				else{
					atexit(SingleTon<_STR>::Release);
				}
			}
			SingleTonRepository<_STR>::_lock.unlock();
		}
		return SingleTon<_STR>::instance;
	}
	TEMPLATE_DEFINE(void)::lock() {
		SingleTon<_STR>::_mutex.lock();
	}
	TEMPLATE_DEFINE(void)::unlock() {
		SingleTon<_STR>::_mutex.unlock();
	}
	TEMPLATE_DEFINE(bool)::try_lock() {
		return SingleTon<_STR>::_mutex.try_lock();
	}
	TEMPLATE_DEFINE(_Mutex_base::native_handle_type)::native_handle() {
		return SingleTon<_STR>::_mutex.native_handle();
	}
	/**
	*	@name : Release
	*	@comment : this method is private, this method is auto call at program terminated
	*/
	TEMPLATE_DEFINE(void)::Release() {
		if (SingleTon<_STR>::instance){
			delete SingleTon<_STR>::instance;
			SingleTon<_STR>::instance = nullptr;
		}
	}
}
#undef TEMPLATE
#undef TEMPLATE_DEFINE
#endif 