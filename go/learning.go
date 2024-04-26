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

package main

import (
	"fmt"
	// "string"
	// "time"
)

func main() {
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

	m := make(map[string]int)

}
