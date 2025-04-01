# ros2_ramp_up

This repository contains a collection of **ROS 2 C++ demos**, which include:

- A **publisher/subscriber demo**
- A **service/client demo**
- **Custom messages & services**
- A **new interface package**
- **Dynamic reconfiguration for the publisher**

## 📌 Testing and Running the Demos

## Publisher/Subscriber Demo (cpp_pubsub)

### **Start the publisher:**

```bash
ros2 run cpp_pubsub minimal_publisher
```

### **Start the subscriber:**

```bash
ros2 run cpp_pubsub minimal_subscriber
```

### **Test dynamic parameters:**
You can dynamically modify parameters for the publisher:

```bash
ros2 param set /minimal_publisher publish_rate 1000
ros2 param set /minimal_publisher message_content "New Message"
```

## Service/Client Demo (cpp_service_demo)

### **Start the service:**

```bash
ros2 run cpp_service_demo service_node 
```

### **Call the service:**

```bash
ros2 run cpp_service_demo client_node 2 4
```

##  Custom Messages & Services

### Custom Message Demo
To run the custom message demo, execute the following commands:

```bash
ros2 run cpp_pubsub num_publisher
ros2 run cpp_pubsub num_subscriber
```

###  Custom Service Demo
To run the custom service demo, execute the following commands:

```bash
ros2 run cpp_service_demo add_three_ints_server
ros2 run cpp_service_demo add_three_ints_client 10 20 30
```

## New Interface Package (more_interfaces)

### **Start publisher/subscriber with custom interface:**

```bash
ros2 run more_interfaces publish_address_book
ros2 run more_interfaces address_book_subscriber
```
