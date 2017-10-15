#pragma once

namespace KumaCore
{
	template <typename T>
	bool contains(const std::vector<T>& vec, const T& val)
	{
		for (auto const& v : vec)
			if (v == val)
				return true;
		return false;
	}

	template <typename T>
	void push_back_unique(std::vector<T>& vec, T&& val)
	{
		if (!contains(vec, val))
			vec.push_back(val);
	}
}