# kubectl
kubectl config get-contexts

kubectl get nodes

kubectl version --output=json

kubectl api-resources

kubectl explain pod

kubectl explain pod.spec.containers
# --------
kubectl run ngx --image=nginx:alpine --dry-run=client -o yaml > pod.yml

kubectl apply -f pod.yml

kubectl get pod

kubectl delete -f pod.yml
# 
kubectl apply -f ngx-pod.yml
kubectl logs ngx-pod
kubectl exec -it ngx-pod -- sh
    cat /etc/os-release
kubectl delete -f ngx-pod.yml
# --------
kubectl create job echo-job --image=busybox --dry-run=client -o yaml >job.yml
kubectl apply -f job.yml

kubectl get job

kubectl get pod
kubectl logs echo-job-n2451
kubectl delete -f job.yml
# --------
kubectl create cj echo-cj --image=busybox --schedule="" --dry-run=client -o yaml > cronjob.yml
kubectl apply -f crontab.yml

kubectl get cj

kubectl get pod
kubectl logs echo-cj-27989602-2z52j
kubectl delete -f cronjob.yml
# --------
kubectl create cm info --from-literal=kkk=vvv --dry-run=client -o yaml > cm.yml
kubectl apply -f cm.yml
kubectl get cm
kubectl describe cm info

kubectl create secret generic user --from-literal=name=root --dry-run=client -o yaml > secret.yml
echo -n "123456" |base64
kubectl apply -f secret.yml
kubectl get secrets
kubectl describe secrets user

kubectl apply -f vol-pod.yml
kubectl get pod
kubectl exec -it vol-pod -- sh
   cd /tmp
   # there will be decoded dir
kubectl delete -f vol-pod.yml
kubectl delete -f cm.yml
kubectl delete -f secret.yml
# --------
vi mariadb-pod.yml
kubectl apply -f mariadb-pod.yml
kubectl get pod
kubectl get pod -o wide

vi wp-pod.yml
kubectl apply -f wp-pod.yml
kubectl get pod -o wide
kubectl port-forward wp-pod 8080:80 &

