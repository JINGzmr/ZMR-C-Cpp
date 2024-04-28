// package main

// import "fmt"

// func main() {
// 	// fmt.Println("hello world")
// 	fmt.Println("zhang" + "minrui")
// 	fmt.Println("1+1=", 2)

// }

// package main

// import (
// 	"fmt"
// 	"time"
// )

// func main() {

// 	i := 2
// 	fmt.Print("write ", i, " as ")
// 	switch i {
// 	case 1:
// 		fmt.Println("one")
// 	case 2:
// 		fmt.Println("two")
// 	case 3:
// 		fmt.Println("three")
// 	}

// 	switch time.Now().Weekday() {
// 	case time.Saturday, time.Sunday:
// 		fmt.Println("It's the weekend")
// 	default:
// 		fmt.Println("It's a weekday")
// 	}

// 	t := time.Now()
// 	switch {
// 	case t.Hour() < 12:
// 		fmt.Println("It's before noon")
// 	default:
// 		fmt.Println("It's after noon")
// 	}

// 	whatAmI := func(i interface{}) {
// 		switch t := i.(type) {
// 		case bool:
// 			fmt.Println("I'm a bool")
// 		case int:
// 			fmt.Println("I'm an int")
// 		default:
// 			fmt.Printf("Don't know type %T\n", t)
// 		}
// 	}
// 	whatAmI(true)
// 	whatAmI(1)
// 	whatAmI("hey")
// }

// int func(int a,int b){

// }

// func myfunc(int a,int b)int{

// }

// package main

// import (
// 	"fmt"
// "string"
// "time"
// )

// func main() {
// var a, b int
// fmt.Scan(&a, &b)
// fmt.Println(a, b)

// num := 0
// var arr [2][2]int
// for i := 0; i < 2; i++ {
// 	for j := 0; j < 2; j++ {
// 		num++
// 		arr[i][j] = num
// 		// fmt.Println(num)
// 	}
// }

// fmt.Println(arr)

// s := make([]string, 4)
// // a := 2
// s[1] = "a"
// s[2] = "b"
// s[3] = "c"
// l := s[:]
// fmt.Println(l)

// m := make(map[string]int)

// }

// ------------变参函数-------------
// package main

// import "fmt"

// func sum(nums ...int) {
// 	fmt.Println(nums, " ")
// 	for _, num := range nums {
// 		fmt.Println(num)
// 	}
// }

// func main() {
// 	sum(1, 2)

// 	arr := []int{1, 2, 3, 4, 5, 6, 7, 8}
// 	sum(arr...)
// }

// ------------闭包------------
// package main

// import "fmt"

// func fun1() func() int {
// 	var i int
// 	i = 0
// 	return func() int {
// 		i++
// 		return i
// 	}
// }

// func main() {
// 	fun2 := fun1()

// 	fmt.Println(fun2())
// 	fmt.Println(fun2())
// 	fmt.Println(fun2())

// 	fun3 := fun1()
// 	fmt.Println(fun3())

// }

//