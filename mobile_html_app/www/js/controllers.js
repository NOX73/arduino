angular.module('starter.controllers', ['ionic'])

.controller('DashCtrl', function($scope, $http) {

  $scope.clickOn = function() {
    $http.get("http://192.168.1.2:3000/?pos=on");
  }

  $scope.clickOff = function() {
    $http.get("http://192.168.1.2:3000/?pos=off");
  }

})

.controller('FriendsCtrl', function($scope, Friends) {
  $scope.friends = Friends.all();
})

.controller('FriendDetailCtrl', function($scope, $stateParams, Friends) {
  $scope.friend = Friends.get($stateParams.friendId);
})

.controller('AccountCtrl', function($scope) {
});
