#pragma once
#include <optional>
#include <string>
#include <vector>
#include "../gltf_read_exception.h"

namespace glTF
{
	enum class AccessorComponentType : int
	{
		Byte = 5120,
		UnsignedByte = 5121,
		Short = 5122,
		UnsignedShort = 5123,
		UnsignedInt = 5125,
		Float = 5126
	};

	enum class AccessorSparseIndicesComponentType : int
	{
		UnsignedByte = 5121,
		UnsignedShort = 5123,
		UnsignedInt = 5125
	};

	enum class AccessorElementsType
	{
		Scalar,
		Vector2,
		Vector3,
		Vector4,
		Matrix2,
		Matrix3,
		Matrix4
	};

	inline int GetAccessorElementsTypeComponentCount(AccessorElementsType type)
	{
		switch (type)
		{
		case AccessorElementsType::Scalar:
			return 1;
		case AccessorElementsType::Vector2:
			return 2;
		case AccessorElementsType::Vector3:
			return 3;
		case AccessorElementsType::Vector4:
			return 4;
		case AccessorElementsType::Matrix2:
			return 4;
		case AccessorElementsType::Matrix3:
			return 9;
		case AccessorElementsType::Matrix4:
			return 16;
		}

		throw GLTFReadException("Invalid accessor element type");
	}

	struct AccessorSparseValues
	{
		int bufferView;
		int byteOffset;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct AccessorSparseIndices
	{
		int bufferView;
		int byteOffset;
		AccessorSparseIndicesComponentType componentType;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct AccessorSparse
	{
		int count;
		AccessorSparseIndices indices;
		AccessorSparseValues values;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct Accessor
	{
		int bufferView;
		int byteOffset;
		AccessorComponentType componentType;
		bool normalized;
		int count;
		AccessorElementsType type;
		std::optional<std::vector<float>> max;
		std::optional<std::vector<float>> min;
		std::optional<AccessorSparse> sparse;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}