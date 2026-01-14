<?php
include 'components/connect.php';
session_start();

if (!isset($_SESSION['user_id'])) {
   header('location:login.php');
   exit;
}

$user_id = $_SESSION['user_id'];

$select_messages = $conn->prepare("SELECT * FROM `Full texts` WHERE user_id = ? ORDER BY sent_at DESC");
$select_messages->execute([$user_id]);
?>

<!DOCTYPE html>
<html lang="en">
<head>
   <meta charset="UTF-8">
   <title>Your Messages</title>
   <link rel="stylesheet" href="css/style.css">
</head>
<body>

<?php include 'components/user_header.php'; ?>

<section class="messages">
   <h1 class="heading">Your Messages</h1>
   <div class="box-container">
      <?php
      if ($select_messages->rowCount() > 0) {
         while ($row = $select_messages->fetch(PDO::FETCH_ASSOC)) {
            echo '<div class="box">';
            echo '<p><strong>You:</strong> ' . htmlspecialchars($row['message']) . '</p>';
            if (!empty($row['admin_reply'])) {
               echo '<p><strong>Admin Reply:</strong> ' . htmlspecialchars($row['admin_reply']) . '</p>';
            } else {
               echo '<p><em>No reply yet.</em></p>';
            }
            echo '<p class="date">' . $row['sent_at'] . '</p>';
            echo '</div>';
         }
      } else {
         echo '<p class="empty">No messages yet!</p>';
      }
      ?>
   </div>
</section>

</body>
</html>
