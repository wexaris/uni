<?php
switch($_GET['action']) {
    case 'list_all': list_all(); break;
    case 'insert': insert(); break;
    case 'delete': delete(); break;
    case 'delete_all': delete_all(); break;
    case 'update': update(); break;
    default: break;
}

function list_all() {
    $db = new db();
    $results = $db->get_all();

    if ($results->num_rows > 0) {
        while($record=$results->fetch_assoc()) {
            print("Id <b>".$record["id"]."</b>,
                product <b>".$record["product"]."</b>,
                quantity <b>".$record['quantity']."</b>,
                phone <b>".$record['phone']."</b>");
            echo "<br><br>";
        }
    }
    else {
        echo "Empty!";
    }
    echo "<br><br>";
}

function insert() {
    $id = $_POST["id"];
    $product = $_POST["product"];
    $quantity = $_POST["quantity"];
    $phone = $_POST["phone"];

    $db = new db();
    if (empty($id)) {
        $db->auto_insert($product, $quantity, $phone);
    }
    else {
        $db->insert($id, $product, $quantity, $phone);
    }

    $affected = $db->get_last_affected();
    if ($affected > 0) {
        echo "Inserted ".$affected." rows <br>";
    }
    else {
        echo "Failed!";
    }
}

function delete() {
    $id = $_POST["id"];

    $db = new db();
    $db->delete($id);

    $affected = $db->get_last_affected();
    if ($affected > 0) {
        echo "Affected ".$affected." rows <br>";
    }
    else {
        echo "Failed!";
    }
}

function delete_all() {
    $db = new db();
    $db->delete_all();

    $affected = $db->get_last_affected();
    if ($affected > 0) {
        echo "Affected ".$affected." rows <br>";
    }
    else {
        echo "Failed!";
    }
}

function update() {
    $id = $_POST["id"];
    $product = $_POST["product"];
    $quantity = $_POST["quantity"];
    $phone = $_POST["phone"];

    $db = new db();
    $db->update($id, $product, $quantity, $phone);

    $affected = $db->get_last_affected();
    if ($affected > 0) {
        echo "Affected ".$affected." rows <br>";
    }
    else {
        echo "Failed!";
    }
}

class db {
    private $myconn;
    private $servername = "localhost";
    private $username = "root";
    private $password = "";
    private $database = "pd2";

    public function __construct() {
        $this->myconn = new mysqli($this->servername, $this->username, $this->password, $this->database);
    }

    public function __destruct() {
        mysqli_close($this->myconn);
    }

    public function get_all() {
        $sql = "SELECT * FROM orders;";
        return $this->query($sql);
    }

    public function insert($id, $product, $quantity, $phone) {
        $sql = "INSERT INTO orders (id,product,quantity,phone) VALUES ($id,'$product',$quantity,'$phone');";
        return $this->query($sql);
    }

    public function auto_insert($product, $quantity, $phone) {
        $sql = "INSERT INTO orders (product,quantity,phone) VALUES ('$product',$quantity,'$phone');";
        return $this->query($sql);
    }

    public function delete($id) {
        $sql = "DELETE FROM orders WHERE id=$id;";
        return $this->query($sql);
    }

    public function delete_all() {
        $sql = "DELETE FROM orders;";
        return $this->query($sql);
    }

    public function update($id, $product, $quantity, $phone) {
        $sql = "UPDATE orders SET product='$product', quantity='$quantity', phone='$phone' WHERE id=$id;";
        return $this->query($sql);
    }

    public function query($sql) {
        $res = $this->myconn->query($sql);
        if ($res) {
            return $res;
        }
        die(mysqli_error($this->myconn));
    }

    public function get_last_affected() {
        return mysqli_affected_rows($this->myconn);
    }
}
?>
