#!/bin/sh
### BEGIN INIT INFO
# Provides:             esme-gpio26-toggle
# Required-Start:       $remote_fs $time
# Required-Stop:        $remote_fs $time
# Default-Start:        3 4 5
# Default-Stop:         0 1 2 6
# Short-Description:    ESME GPIO#26 toggle service
### END INIT INFO

DAEMON=/usr/bin/esme-gpio-toggle
NAME=esme-gpio-toggle
PIDFILE=/var/run/${NAME}.pid
GPIO_ID=26

case "$1" in

    start)
        echo "Starting $NAME..."
        start-stop-daemon --start --background \
            --make-pidfile --pidfile $PIDFILE \
            --exec $DAEMON -- --gpio $GPIO_ID
        ;;

    stop)
        echo "Stopping $NAME..."
        start-stop-daemon --stop --pidfile $PIDFILE --retry 5
        rm -f $PIDFILE
        ;;

    restart)
        echo "Restarting $NAME..."
        $0 stop
        sleep 1
        $0 start
        ;;

    status)
        if [ -f "$PIDFILE" ]; then
            PID=$(cat "$PIDFILE")
            if kill -0 "$PID" 2>/dev/null; then
                echo "Status of esme-gpio-toggle for GPIO#26: running with PID=$PID"
            else
                echo "Status of esme-gpio-toggle for GPIO#26: stopped"
            fi
        else
            echo "Status of esme-gpio-toggle for GPIO#26: stopped"
        fi
        ;;

    *)
        echo "Usage : esme-gpio26-toggle (start | stop | restart | status )"
        exit 1
        ;;
esac

exit 0
INSTALL_DIR=${D}
