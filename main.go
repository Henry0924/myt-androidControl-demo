package main

import (
	"flag"
	"fmt"
	"log"
	"math"
	"os"
	"reflect"
	"syscall"
	"time"
	"unicode/utf8"
	"unsafe"
)

var (
	command = flag.String("command", "move", "操作指令, click--点击, move--滑动, screenshot--截图")
	host    = flag.String("host", "", "安卓host，例192.168.100.10")
	x1      = flag.Int("x1", 200, "x轴坐标x1")
	y1      = flag.Int("y1", 200, "y轴坐标y1")
	x2      = flag.Int("x2", 600, "滑动终点x轴坐标x2")
	y2      = flag.Int("y2", 200, "滑动终点y轴坐标y2")
)

func StrPtr(s string) uintptr {
	p, _ := syscall.BytePtrFromString(s)
	return uintptr(unsafe.Pointer(p))
}

func PtrStr(p uintptr) string {
	return syscall.UTF16ToString(*(*[]uint16)(unsafe.Pointer(&p)))
}

func IntPtr(i int) uintptr {
	return uintptr(i)
}

func PtrInt(u uintptr) int {
	return int(u)
}

func readMemory(addr uintptr, size int) []byte {
	return *(*[]byte)(unsafe.Pointer(&reflect.SliceHeader{
		Data: addr,
		Len:  size,
		Cap:  size,
	}))
}

var (
	Lib    *syscall.DLL
	Handle uintptr
)

func getY(k, x, x1, y1 float64) float64 {
	return math.Floor(k*(x-x1) + y1)
}

func getX(k, y, x1, y1 float64) float64 {
	return math.Floor((y-y1)/k + x1)
}

func Move(x1, y1, x2, y2 int) {
	k := float64(0)
	if (float64(x2) - float64(x1)) != 0 {
		k = (float64(y2) - float64(y1)) / (float64(x2) - float64(x1))
	}

	touchDown := Lib.MustFindProc("touchDown")
	touchDown.Call(Handle, 0, IntPtr(x1), IntPtr(y1))

	touchMove := Lib.MustFindProc("touchMove")
	absX := math.Abs(float64(x2 - x1))
	absY := math.Abs(float64(y2 - y1))
	var mx, my, t float64
	if absX > absY {
		t = math.Floor(absX / 30)
		for i := 0; i < int(t); i++ {
			if x2 > x1 {
				mx = float64(x1 + i*30)
			} else {
				mx = float64(x1 - i*30)
			}
			my = getY(k, mx, float64(x1), float64(y1))
			touchMove.Call(Handle, 0, IntPtr(int(mx)), IntPtr(int(my)))

			time.Sleep(time.Millisecond)
		}
	} else {
		t = math.Floor(absY / 30)
		for i := 0; i < int(t); i++ {
			if y2 > y1 {
				my = float64(y1 + i*30)
			} else {
				my = float64(y1 - i*30)
			}
			mx = getX(k, my, float64(x1), float64(y1))
			touchMove.Call(Handle, 0, IntPtr(int(mx)), IntPtr(int(my)))

			time.Sleep(time.Millisecond)
		}
	}
	touchMove.Call(Handle, 0, IntPtr(x2), IntPtr(y2))
	time.Sleep(time.Millisecond)

	touchUp := Lib.MustFindProc("touchUp")
	touchUp.Call(Handle, 0, IntPtr(x2), IntPtr(y2))
}

func TakeCaptrueCompress() string {
	takeCaptrueCompress := Lib.MustFindProc("takeCaptrueCompress")
	var dataLen int
	ret, _, _ := takeCaptrueCompress.Call(Handle, 0, 0, uintptr(unsafe.Pointer(&dataLen)))

	b := readMemory(ret, dataLen)
	fileName := fmt.Sprintf("%d.png", time.Now().Unix())
	file, err := os.OpenFile(fileName, os.O_CREATE, 0)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	_, err = file.Write(b)
	if err != nil {
		log.Fatal(err)
	}

	freeRpcPtr := Lib.MustFindProc("freeRpcPtr")
	freeRpcPtr.Call(ret)

	return fileName
}

func Keypress() {
	keyPress := Lib.MustFindProc("keyPress")
	ret, _, _ := keyPress.Call(Handle, IntPtr(24))
	log.Println("ret: ", ret)
}

func Click(x int, y int) {
	touchClick := Lib.MustFindProc("touchClick")
	ret, _, _ := touchClick.Call(Handle, 0, IntPtr(x), IntPtr(y))
	log.Println("ret: ", ret)
}

func SendText() {
	log.Println("utf8: ", utf8.ValidString("你好"))
	sendText := Lib.MustFindProc("sendText")
	ret, _, _ := sendText.Call(Handle, StrPtr("你好"))
	log.Println("ret: ", ret)
}

func OpenApp() {
	openApp := Lib.MustFindProc("openApp")
	ret, _, _ := openApp.Call(Handle, StrPtr("tv.danmaku.bili"))
	log.Println("ret: ", ret)
}

func StopApp() {
	stopApp := Lib.MustFindProc("stopApp")
	ret, _, _ := stopApp.Call(Handle, StrPtr("tv.danmaku.bili"))
	log.Println("ret: ", ret)
}

func main() {
	flag.Parse()

	if *host == "" {
		log.Fatal("host不能为空")
	}

	Lib = syscall.MustLoadDLL("libmytrpc.dll")
	proc := Lib.MustFindProc("openDevice")
	Handle, _, _ = proc.Call(StrPtr(*host), 9083, 10)

	defer func() {
		closeDevice := Lib.MustFindProc("closeDevice")
		closeDevice.Call(Handle)
	}()

	switch *command {
	case "click":
		Click(*x1, *y1)
		log.Printf("click: x1-%d, y1-%d", *x1, *y1)
	case "move":
		Move(*x1, *y1, *x2, *y2)
		log.Printf("move: x1-%d, y1-%d; x2-%d, y2-%d", *x1, *y1, *x2, *y2)
	case "screenshot":
		fileName := TakeCaptrueCompress()
		log.Printf("screenshot: %s", fileName)
	default:
		log.Fatal("command错误")
	}

}
