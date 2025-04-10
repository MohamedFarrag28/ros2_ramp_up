// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_custom_interfaces:msg/Sphere.idl
// generated code does not contain a copyright notice

#ifndef MY_CUSTOM_INTERFACES__MSG__DETAIL__SPHERE__STRUCT_HPP_
#define MY_CUSTOM_INTERFACES__MSG__DETAIL__SPHERE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__my_custom_interfaces__msg__Sphere __attribute__((deprecated))
#else
# define DEPRECATED__my_custom_interfaces__msg__Sphere __declspec(deprecated)
#endif

namespace my_custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Sphere_
{
  using Type = Sphere_<ContainerAllocator>;

  explicit Sphere_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->radius = 0.0f;
    }
  }

  explicit Sphere_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->radius = 0.0f;
    }
  }

  // field types and members
  using _radius_type =
    float;
  _radius_type radius;
  using _center_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _center_type center;

  // setters for named parameter idiom
  Type & set__radius(
    const float & _arg)
  {
    this->radius = _arg;
    return *this;
  }
  Type & set__center(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->center = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_custom_interfaces::msg::Sphere_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_custom_interfaces::msg::Sphere_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_custom_interfaces::msg::Sphere_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_custom_interfaces::msg::Sphere_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_custom_interfaces__msg__Sphere
    std::shared_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_custom_interfaces__msg__Sphere
    std::shared_ptr<my_custom_interfaces::msg::Sphere_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Sphere_ & other) const
  {
    if (this->radius != other.radius) {
      return false;
    }
    if (this->center != other.center) {
      return false;
    }
    return true;
  }
  bool operator!=(const Sphere_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Sphere_

// alias to use template instance with default allocator
using Sphere =
  my_custom_interfaces::msg::Sphere_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_custom_interfaces

#endif  // MY_CUSTOM_INTERFACES__MSG__DETAIL__SPHERE__STRUCT_HPP_
