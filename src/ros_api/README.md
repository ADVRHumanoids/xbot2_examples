# Xbot2 ROS API
[Back to home](../../README.md)

## Python 
Follow the [provided *Jupyter Notebook*](ros_api_tutorial.ipynb) (install with `pip install notebook` if needed) to get a grasp on how to control an Xbot2 robot in joint space from a python ROS node. Just type the command

```bash
jupyter notebook ros_api_tutorial.ipynb
```

---

*Note: to run a jupyter notebook from inside a **docker** container, use the following command*

```
jupyter notebook --no-browser --ip=0.0.0.0 <notebook-file>. 
```

*and make sure that port `8888` is being published to the host machine*. Our example docker provides the `notebook_docker` alias for the sake of convenience.

## C++
The same behavior can be equivalently implemented in C++, as shown by [this example](ros_api_tutorial.cpp).
After compilation, it can be executed with

```bash
cd <build-dir> && ./src/ros_api/ros_api_tutorial 
```

