<?php
include 'components/connect.php';
session_start();
if (isset($_SESSION['user_id'])) {
    $user_id = $_SESSION['user_id'];
} else {
    $user_id = 0;
}

$message = [];

if (isset($_POST['send_message'])) {
    $user_message = trim($_POST['message']);

    if ($user_id == 0) {
        $_SESSION['flash_message'] = "Please login to send a message.";
    } elseif (empty($user_message)) {
        $_SESSION['flash_message'] = "Message cannot be empty.";
    } else {
        $insert = $conn->prepare("INSERT INTO `Full texts` (user_id, message) VALUES (?, ?)");
        $insert->execute([$user_id, $user_message]);
        $_SESSION['flash_message'] = "Thank you! Your message has been sent successfully.";
    }

    
    header("Location: chat.php"); 
    exit;
}


if (isset($_SESSION['flash_message'])) {
    $message[] = $_SESSION['flash_message'];
    unset($_SESSION['flash_message']);
}


$select_messages = $conn->prepare("SELECT * FROM `Full texts` WHERE user_id = ? ORDER BY sent_at DESC");
$select_messages->execute([$user_id]);

$unique_messages = [];
$seen_messages = [];

while ($row = $select_messages->fetch(PDO::FETCH_ASSOC)) {
    $text = trim($row['message']);
    if (!in_array($text, $seen_messages)) {
        $unique_messages[] = $row;
        $seen_messages[] = $text;
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
   <meta charset="UTF-8" />
   <meta name="viewport" content="width=device-width, initial-scale=1" />
   <title>Contact Us</title>
   <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.1.1/css/all.min.css" />
   <link rel="stylesheet" href="css/style.css" />

</head>
<body>

<?php include 'components/user_header.php'; ?>

<div class="contact-container">
   <h2>Send Message TO Admin</h2>

   <?php if (!empty($message) && is_array($message)): ?>
      <?php foreach ($message as $msg): ?>
         <div class="message-success"><?= htmlspecialchars($msg) ?></div>
      <?php endforeach; ?>
   <?php endif; ?>

   <form action="" method="post">
      <textarea name="message" placeholder="Type your message here..." required></textarea>
      <button type="submit" name="send_message">Send Message</button>
   </form>

   <h2> <strong>Your Previous Messages</strong> </h2>

   <?php if (count($unique_messages) > 0): ?>
      <?php foreach ($unique_messages as $msg): ?>
         <div class="message-box">
            <p><strong>Your Message:</strong><br><?= nl2br(htmlspecialchars($msg['message'])) ?></p>
            <p><small>Sent at: <?= htmlspecialchars($msg['sent_at']) ?></small></p>
            <?php if (!empty($msg['admin_reply'])): ?>
               <hr>
               <p><strong>Admin Reply:</strong><br><?= nl2br(htmlspecialchars($msg['admin_reply'])) ?></p>
            <?php endif; ?>
         </div>
      <?php endforeach; ?>
   <?php else: ?>
      <p>You have not sent any messages.</p>
   <?php endif; ?>
</div>

<?php include 'components/footer.php'; ?>

</body>
</html>
