<?php
include '../components/connect.php';
session_start();

if (!isset($_SESSION['admin_id'])) {
   header('location:admin_login.php');
   exit;
}

$message = [];

if (isset($_POST['send_reply'])) {
   $message_id = $_POST['message_id'];
   $admin_reply = $_POST['admin_reply'];

   $update = $conn->prepare("UPDATE `Full texts` SET admin_reply = ? WHERE id = ?");
   $update->execute([$admin_reply, $message_id]);

   $message[] = "Reply sent successfully!";
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
   <meta charset="UTF-8">
   <title>Admin Messages</title>
   <link rel="stylesheet" href="../css/admin_style.css">
   <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">

</head>
<body>

<?php include '../components/admin_header.php'; ?>

<section class="messages">
   <h1 class="heading">User Messages</h1>

   <div class="box-container">
      <?php
         $select = $conn->prepare("SELECT * FROM `Full texts` ORDER BY id DESC");
         $select->execute();

         if ($select->rowCount() > 0) {
            while ($row = $select->fetch(PDO::FETCH_ASSOC)) {
      ?>
         <div class="box">
            <p><strong>User ID:</strong> <?= htmlspecialchars($row['user_id']); ?></p>
            <p><strong>Message:</strong><br><?= nl2br(htmlspecialchars($row['message'])); ?></p>
            <p><strong>Sent at:</strong> <?= $row['sent_at']; ?></p>

            <form method="post">
               <input type="hidden" name="message_id" value="<?= $row['id']; ?>">
               <textarea name="admin_reply" rows="4" placeholder="Type your reply..." required><?= htmlspecialchars($row['admin_reply']); ?></textarea>
               <button type="submit" name="send_reply" class="btn">Send Reply</button>
            </form>
         </div>
      <?php
            }
         } else {
            echo '<p class="empty">No messages found!</p>';
         }
      ?>
   </div>
</section>

</body>
</html>
