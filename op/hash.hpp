#ifndef _CXXREDIS_OP_HASH_HPP_
#define _CXXREDIS_OP_HASH_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>

namespace redis {

	class client;
	class reply;

	namespace op {

		class hash {
		public:
			hash(client& cli);
			~hash();

			/**
			* ɾ����ϣ�� key �е�һ������ָ���򣬲����ڵ��򽫱����ԡ�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:O(N)�� N ΪҪɾ�������������
			* ����ֵ:���ɹ��Ƴ�����������������������Ե���
			*/
			template <class... Args>
			long long del(const std::string& key, Args... fields);

			/**
			* �鿴��ϣ�� key �У������� field �Ƿ���ڡ�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* �����ϣ�����и����򣬷��� 1 ��
			* �����ϣ�������и����򣬻� key �����ڣ����� 0 ��
			*/
			bool exist(const std::string& key, const std::string& field);

			/**
			* ���ع�ϣ�� key �и����� field ��ֵ��
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* �������ֵ��
			* �������򲻴��ڻ��Ǹ��� key ������ʱ������ nil ��
			*/
			std::string get(const std::string& key, const std::string& field);

			/**
			* ���ع�ϣ�� key �У����е����ֵ
			* �ڷ���ֵ�����ÿ������(field name)֮�������ֵ(value)�����Է���ֵ�ĳ����ǹ�ϣ����С��������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(N), N Ϊ��ϣ���Ĵ�С��
			* ����ֵ��
			* ���б���ʽ���ع�ϣ����������ֵ��
			* �� key �����ڣ����ؿ��б���
			*/
			reply getAll(const std::string& key);

			/**
			* Ϊ��ϣ�� key �е��� field ��ֵ�������� increment ��
			* ����Ҳ����Ϊ�������൱�ڶԸ�������м���������
			* ��� key �����ڣ�һ���µĹ�ϣ����������ִ�� HINCRBY ���
			* ����� field �����ڣ���ô��ִ������ǰ�����ֵ����ʼ��Ϊ 0 ��
			* ��һ�������ַ���ֵ���� field ִ�� HINCRBY ������һ������
			* ��������ֵ�������� 64 λ(bit)�з������ֱ�ʾ֮�ڡ�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ִ�� HINCRBY ����֮�󣬹�ϣ�� key ���� field ��ֵ��
			*/
			long long incrBy(const std::string& key, const std::string& field, long long increment);

			/**
			* Ϊ��ϣ�� key �е��� field ���ϸ��������� increment ��
			* �����ϣ����û���� field ����ô HINCRBYFLOAT ���Ƚ��� field ��ֵ��Ϊ 0 ��Ȼ����ִ�мӷ�������
			* ����� key �����ڣ���ô HINCRBYFLOAT ���ȴ���һ����ϣ�����ٴ����� field �������ִ�мӷ�������
			* ����������һ����������ʱ������һ������
			* �� field ��ֵ�����ַ�������(��Ϊ redis �е����ֺ͸����������ַ�������ʽ���棬�������Ƕ������ַ������ͣ�
			* �� field ��ǰ��ֵ����������� increment ���ܽ���(parse)Ϊ˫���ȸ�����(double precision floating point number)
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ִ�мӷ�����֮�� field ���ֵ��
			*/
			std::string incrByFloat(const std::string& key, const std::string& field, double increment);

			/**
			* ���ع�ϣ�� key �е�������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(N)�� N Ϊ��ϣ���Ĵ�С��
			* ����ֵ��
			* һ��������ϣ����������ı���
			* �� key ������ʱ������һ���ձ���
			*/
			reply keys(const std::string& key);

			/**
			* ���ع�ϣ�� key �����������
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ��ϣ�������������
			* �� key ������ʱ������ 0 ��
			*/
			long long len(const std::string& key);

			/**
			* ���ع�ϣ�� key �У�һ�������������ֵ��
			* ����������򲻴����ڹ�ϣ������ô����һ�� nil ֵ��
			* ��Ϊ�����ڵ� key ������һ���չ�ϣ�������������Զ�һ�������ڵ� key ���� HMGET ����������һ��ֻ���� nil ֵ�ı���
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(N)�� N Ϊ�������������
			* ����ֵ��
			* һ���������������Ĺ���ֵ�ı�����ֵ������˳��͸��������������˳��һ����
			*/
			template<class... Args>
			reply mget(const std::string& key, Args... fields);

			/**
			* ͬʱ����� field-value (��-ֵ)�����õ���ϣ�� key �С�
			* ������Ḳ�ǹ�ϣ�����Ѵ��ڵ���
			* ��� key �����ڣ�һ���չ�ϣ����������ִ�� HMSET ������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(N)�� N Ϊ field-value �Ե�������
			* ����ֵ��
			* �������ִ�гɹ������� OK ��
			* �� key ���ǹ�ϣ��(hash)����ʱ������һ������
			*/
			template<class... Args>
			reply mset(const std::string& key, std::initializer_list<Args>... pairs);

			/**
			* ����ϣ�� key �е��� field ��ֵ��Ϊ value ��
			* ��� key �����ڣ�һ���µĹ�ϣ�������������� HSET ������
			* ����� field �Ѿ������ڹ�ϣ���У���ֵ�������ǡ�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ��� field �ǹ�ϣ���е�һ���½��򣬲���ֵ���óɹ������� 1 ��
			* �����ϣ������ field �Ѿ������Ҿ�ֵ�ѱ���ֵ���ǣ����� 0 ��
			*/
			long long set(const std::string& key, const std::string& field, const std::string& value);

			/**
			* ����ϣ�� key �е��� field ��ֵ����Ϊ value �����ҽ����� field �����ڡ�
			* ���� field �Ѿ����ڣ��ò�����Ч��
			* ��� key �����ڣ�һ���¹�ϣ����������ִ�� HSETNX ���
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ���óɹ������� 1 ��
			* ����������Ѿ�������û�в�����ִ�У����� 0 ��
			*/
			bool setNx(const std::string& key, const std::string& field, const std::string& value);

			/**
			* ���ع�ϣ�� key ���������ֵ��
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(N)�� N Ϊ��ϣ���Ĵ�С��
			* ����ֵ��
			* һ��������ϣ��������ֵ�ı���
			* �� key ������ʱ������һ���ձ�
			*/
			reply vals(const std::string& key);

			/**
			*
			* ���ڵ�����ǰ���ݿ��е����ݿ����
			*/
			reply scan(int cursor, const std::string& matchPattern = "*", int count = 10);

			/**
			* ���ع�ϣ�� key �У� ������� field �������ֵ���ַ������ȣ�string length����
			* ��������ļ������򲻴��ڣ� ��ô����� 0 ��
			* ���ð汾��>= 3.2.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��һ��������
			*/
			long long strLen(const std::string& key, const std::string& field);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/hash.hpp"
#endif

#endif